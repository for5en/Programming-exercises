class Karta
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

    def to_s
        s = "#";
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
    end
end

k = Karta.new(12, :kier)
puts(k.to_s)