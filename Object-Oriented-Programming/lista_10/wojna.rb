# mixin
module Zapis
    def save_to_file(filename)
        File.open(filename, 'wb') { |f| f.write(Marshal.dump(self)) }
    end
  
    module Metody
        def load_from_file(filename)
            File.open(filename, 'rb') { |f| Marshal.load(f) }
        end
    end
  
    def self.included(base)
        base.extend(Metody)
    end
end
  
# schemat rozgrywki
class RozgrywkaTemplate
    def initialize(gracze)
        @gracze = gracze
    end
  
    def rozpocznij
        catch :zapisz_i_wyjdz do
            while kontynuuj
                wyswietl_stan
                wykonaj_ture
                puts "\n"
            end
        end
        puts "Zapisywanie..."
        zapisz_gre
    end
  
    def kontynuuj
        @gracze.size > 1
    end
  
    def wyswietl_stan
        for gracz in @gracze
            puts "#{gracz.pseudonim} ma #{gracz.l_kart} kart"
        end          
    end
  
    def wykonaj_ture
    end
  
    def zapisz_gre
    end
end
  

class Karta
    include Comparable

    KOLORY = {
        kier:   "♥️",
        karo:   "♦️",
        trefl:  "♣️",
        pik:    "♠️"
    }

    attr_reader :waga, :kolor

    def initialize(waga, kolor)
        @waga = waga
        @kolor = kolor
    end


    @@talia = []

    def self.stworz_talie
        for k in KOLORY
            for w in (2..14)
                @@talia << Karta.new(w, k[0])
            end
        end
        @@talia.shuffle!
        @@talia.shuffle!
    end

    def self.stworz_mala_talie
        for k in KOLORY
            for w in (2..8)
                @@talia << Karta.new(w, k[0])
            end
        end
        @@talia.shuffle!
        @@talia.shuffle!
    end

    def self.wydaj_karte
        if @@talia.empty?
            raise 'Koniec talii'
        else
            return @@talia.pop
        end
    end

    def self.talia
        return @@talia
    end

    def to_s
        s = "#"
        case waga
        when 11
            s += "walet "
        when 12
            s += "dama "
        when 13
            s += "krol "
        when 14
            s += "as "
        else
            s += (waga.to_s + " ")
        end
        s += KOLORY[kolor]
        return s
    end

    def <=>(inna)
        self.waga <=> inna.waga
    end
end

class Gracz
    attr_reader :pseudonim

    def initialize(pseudonim)
        @pseudonim = pseudonim
        @talia = []
    end

    def dodaj_karte(karta)
        @talia.unshift(karta)
    end
    
    def ruch
        puts "#{@pseudonim} nacisnij Enter, aby wykonac ruch... (lub s, aby zapisac i wyjsc)"
        if gets.chomp == "s"
            throw :zapisz_i_wyjdz
        end
        return @talia.pop
    end

    def l_kart
        return @talia.size
    end
end

class Komputer
    attr_reader :pseudonim

    def initialize(pseudonim)
        @pseudonim = pseudonim
        @talia = []
    end

    def dodaj_karte(karta)
        @talia.unshift(karta)
    end

    def ruch
        return @talia.pop
    end

    def l_kart
        return @talia.size
    end
end

class Gra < RozgrywkaTemplate
    include Zapis

    def initialize(talia, gracze)
        super(gracze)
        @talia = talia
  
        l_graczy = @gracze.size 
        l_kart = @talia.size

        gracz_index = 0
        for karta in @talia
            @gracze[gracz_index].dodaj_karte(karta)
            gracz_index = (gracz_index + 1) % @gracze.size
        end
    end
  
    def zapisz_gre
        save_to_file("save.dat")
    end
  
    def self.load
        load_from_file("save.dat")
    end
  
    def wykonaj_ture
        tura(@gracze, [])
    end
  
    def tura(gracze, wygrane)
        win_karta = nil
        karty = []
        remisy = []
        usunieci = []
        
        for gracz in gracze
            if gracz.l_kart >= 1
                karty << {gracz: gracz, karta: gracz.ruch}
                wygrane << karty.last[:karta]

                puts "#{gracz.pseudonim} rzuca #{karty.last[:karta]}"

                if win_karta.nil? || win_karta < karty.last[:karta]
                    win_karta = karty.last[:karta]
                end
            else
                puts "#{gracz.pseudonim} przegrywa z powodu braku kart"
                usunieci << gracz
            end
        end

        for karta in karty
            if karta[:karta] == win_karta
                remisy << karta[:gracz]
            end
        end

        if remisy.size > 1
            for gracz in remisy
                if gracz.l_kart < 1
                    puts "#{gracz.pseudonim} przegrywa z powodu braku kart"
                    usunieci << gracz
                end
            end
        end

        for gracz in usunieci
            remisy.delete(gracz)
            gracze.delete(gracz)
            @gracze.delete(gracz)
        end

        if remisy.size == 0
            puts "Wszyscy gracze przegrali, brak zwyciezcy"
        elsif remisy.size == 1
            puts "Wojne wygrywa gracz #{remisy.last.pseudonim}!"
            for karta in wygrane
                remisy.last.dodaj_karte(karta)
            end
        else 
            puts "WOJNA!"
            for gracz in remisy
                wygrane << gracz.ruch
                puts "#{gracz.pseudonim} rzuca 🂠"
            end
            tura(remisy, wygrane)
        end
    end
end

Karta.stworz_talie
ja = Gracz.new("Igor")
pc = Komputer.new("PC")
pc2 = Komputer.new("PC2")

gra = Gra.new(Karta.talia, [ja, pc, pc2])
if File.exist?("save.dat")
    puts "Czy wczytać zapis gry? (y/n)"
    if gets.chomp == "y"
        gra = Gra.load
        puts "Wczytano zapis gry"
    end
end
gra.rozpocznij
