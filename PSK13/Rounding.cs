using System;

class Rounding
{
    public static decimal RoundUp(decimal number, int places) // округляет число вверх до нужного знака
    {
        decimal factor = RoundFactor(places);
        number *= factor;
        number = Math.Ceiling(number);
        number /= factor;
        return number;
    }

    public static decimal RoundDown(decimal number, int places) // округляет число вниз до нужного знака
    {
        decimal factor = RoundFactor(places);
        number *= factor;
        number = Math.Floor(number);
        number /= factor;
        return number;
    }

    public static decimal RoundFactor(int places) // округляет число до нужного знака
    {
        decimal factor = 1m;
        if (places < 0)
        {
            places = -places;
            for (int i = 0; i < places; i++) { factor /= 10m; }
        }
        else
        {
            for (int i = 0; i < places; i++) { factor *= 10m; }
        }

        return factor;
    }
}