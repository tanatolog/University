using System;

public class TDate // класс описывающий дату
{
	public int day;
    public int month;
    public int year;

    private int LeapYear(int Y) // определение весокосного года
    {
        return (1 - (Y % 4 + 2) % (Y % 4 + 1)) * ((Y % 100 + 2) % (Y % 100 + 1)) + (1 - (Y % 400 + 2) % (Y % 400 + 1));
    }

    private int DaysinMonth(int M, int Y) // расчет дней в месяце
    {
        return (28 + (M + M / 8) % 2 + 2 % M + (1 + LeapYear(Y)) / M + 1 / M - LeapYear(Y) / M);
    }

    private int DayofWeek(int D, int M, int Y) // расчет дня недели
    {
        if (M > 2) { M -= 2; }
        else
        {
            M += 10;
            Y -= 1;
        }
        return (D + (13 * M - 1) / 5 + Y + Y / 4 - Y / 100 + Y / 400) % 7;
    }

    private string DayName(int D) // определение имени дня недели
    {
        string result = "";
        switch (D)
        {
            case 1:
                result = "Понедельник";
                break;
            case 2:
                result = "Вторник";
                break;
            case 3:
                result = "Среда";
                break;
            case 4:
                result = "Четверг";
                break;
            case 5:
                result = "Пятница";
                break;
            case 6:
                result = "Суббота";
                break;
            case 0:
                result = "Воскресенье";
                break;
        }
        return result;
    }

    private bool Nonworking(int D, int M, int Y) // определение нерабочего дня
    {
        int name = DayofWeek(D, M, Y);
        if ((name == 6) || (name == 0) ||
            ((M == 1) && (D < 9)) || ((M == 2) && (D == 23)) || ((M == 3) && (D == 8)) || ((M == 5) && ((D == 1) || (D == 9))) ||
            ((M == 6) && (D == 12)) || ((M == 11) && (D == 4))) { return true; }
        else { return false; }
    }

    private int JulianDay(int D, int M, int Y) // расчет юлианского дня
    {
        return ((1461 * (Y + 4800 + (M - 14) / 12)) / 4 + (367 * (M - 2 - 12 * ((M - 14) / 12))) / 12 - (3 * ((Y + 4900 + (M - 14) / 12) / 100)) / 4 + D - 32075);
    }

    private void DateTest() // исправление несуществующей даты на существующую
    {
        if (day == 0) { day = 1; }
        if (month == 0) { month = 1; }
        if (month > 12) { month = 12; }
        if (year == 0) { year = 1; }
        if (day > DaysinMonth(month, year)) { day = DaysinMonth(month, year); }
    }

    public int Quantity(int D, int M, int Y) // расчет количества дней между датами
    {
        return (JulianDay(D, M, Y) - JulianDay(day, month, year));
    }

    public int Quantity(string date) // расчет количества дней между датами
    {
        date = date.Replace(".", "");
        if ((date.Length > 1) && (int.TryParse(date.Substring(0, 2), out int D) == true)) ;
        else { D = 1; }
        if ((date.Length > 2) && (int.TryParse(date.Substring(2, 2), out int M) == true)) ;
        else { M = 1; }
        if ((date.Length > 3) && (int.TryParse(date.Substring(4), out int Y) == true)) ;
        else { Y = 1; }
        return (JulianDay(D, M, Y) - JulianDay(day, month, year));
    }

    public string DayName() // возвращает название текущего дня
    {
        return DayName(DayofWeek(day, month, year));
    }

    public void Int(string date) // принимает дату в виде строки
    {
        date = date.Replace(".", "");
        if ((date.Length > 1) && (int.TryParse(date.Substring(0, 2), out day) == true)) ;
        else { day = 1; }
        if ((date.Length > 2) && (int.TryParse(date.Substring(2, 2), out month) == true)) ;
        else { month = 1; }
        if ((date.Length > 3) && (int.TryParse(date.Substring(4), out year) == true)) ;
        else { year = 1; }
    }

    public string String() // возвращает дату в виде строки
    {
        string tmpD, tmpM;
        if (month < 10) { tmpM = "0" + Convert.ToString(month); }
        else { tmpM = Convert.ToString(month); }
        if (day < 10) { tmpD = "0" + Convert.ToString(day); }
        else { tmpD = Convert.ToString(day); }
        return (tmpD + "." + tmpM + "." + Convert.ToString(year));
    }

    public bool Nonworking() // определяет является ли текущий день нерабочим
    {
        return Nonworking(day, month, year);
    }

    public int DaysinMonth() // определяет количество дней в текущем месяце
    {
        return DaysinMonth(month, year);
    }

    public TDate(string DS) // конструктор класса
	{
        Int(DS);
        DateTest();
    }

    public TDate(int D = 1, int M = 1, int Y = 1) // конструктор класса
    {
        day = D;
        month = M;
        year = Y;
        DateTest();
    }
}
