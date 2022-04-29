package OOP.Provided;
import java.util.*;

public class CasaDeBurritoImpl implements CasaDeBurrito
{
    private int id;
    private String name;
    private int dist;
    private Set<String> menu;
    private int rate_cnt;
    private int rate_sum;
    private Map<Integer, Integer> rates; // <id, rate>

    public CasaDeBurritoImpl(int id, String name, int dist, Set<String> menu)
    {
        this.id = id;
        this.name = name;
        this.dist = dist;
        this.menu = menu;
        this.rate_cnt = 0;
        this.rate_sum = 0;
        this.rates = new HashMap<Integer, Integer>();
    }

    public CasaDeBurritoImpl(CasaDeBurrito other)
    {
        this.id = other.getId();
        this.name = other.getName();
        this.dist = other.distance();
        this.menu = new HashSet<String>(((CasaDeBurritoImpl) other).menu);
        this.rate_cnt = other.numberOfRates();
        this.rate_sum = ((CasaDeBurritoImpl) other).rate_sum;
        this.rates = new HashMap<Integer, Integer>(((CasaDeBurritoImpl) other).rates);
    }

    @Override
    public int getId()
    {
        return id;
    }

    @Override
    public String getName()
    {
        return name;
    }

    @Override
    public int distance()
    {
        return dist;
    }

    @Override
    public boolean isRatedBy(Profesor p)
    {
        if (this.rates.containsKey(p.getId()))
            return true;
        return false;
    }

    @Override
    public CasaDeBurrito rate(Profesor p, int r) throws RateRangeException
    {
        int id = p.getId();
        if (r < 0 || 5 < r)
            throw new RateRangeException();
        if (this.rates.containsKey(id))
        {
            this.rate_sum += (r - this.rates.get(id));
            this.rates.replace(id, r);
        }
        else
        {
            this.rates.put(id, r);
            this.rate_cnt++;
            this.rate_sum += r;
        }
        return this;
    }

    @Override
    public int numberOfRates()
    {
        return rate_cnt;
    }

    @Override
    public double averageRating()
    {
        return (double) rate_sum / (double) rate_cnt;
    }
    
    @Override
    public String toString()
    {
        String str = "CasaDeBurrito: " + this.name;
        str += "\nId: " + this.id;
        str += "\nDistance: " + this.dist;
        str += "\nMenu: ";
        String[] menu = (String[]) this.menu.toArray();
        Arrays.sort(menu);
        for (int i = 0; i < menu.length; i++)
        {
            str += menu[i];
            if(i < menu.length - 1)
                str += ", ";
            else
                str += ".";
        }
        return str;
    }

    @Override
    public int compareTo(CasaDeBurrito o) 
    {
        if (this.id < o.getId())
            return -1;
        else if (this.id > o.getId())
            return 1;
        else
            return 0;
    }

    /*
    public int profesorRate(Profesor p)
    {
        int id = p.getId();
        if (this.rates.containsKey(id))
            return this.rates.get(id);
        return -1;
    }
    */

}