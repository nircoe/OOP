package OOP.Solution;

import OOP.Provided.CasaDeBurrito;
import OOP.Provided.Profesor;
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
        this.menu = new HashSet<>(menu);
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
        if (rate_cnt == 0) return 0;

        return (double) rate_sum / (double) rate_cnt;
    }
    
    @Override
    public String toString()
    {
        StringBuilder str = new StringBuilder("CasaDeBurrito: " + this.name).append(".");
        str.append("\nId: ").append(this.id).append(".");
        str.append("\nDistance: ").append(this.dist).append(".");
        str.append("\nMenu: ");
        Object[] menu = this.menu.toArray();
        Arrays.sort(menu);
        for (int i = 0; i < menu.length; i++)
        {
            str.append(menu[i].toString());
            if(i < menu.length - 1)
                str.append(", ");
            else
                str.append(".");
        }
        if (menu.length == 0)
            str.append(".");
        return str.toString();
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

    @Override
    public boolean equals(Object obj) {
        if (obj == this) return true;
        if (!(obj instanceof CasaDeBurrito)) return false;
        return ((CasaDeBurrito) obj).getId() == this.id;
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