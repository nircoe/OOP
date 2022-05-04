package OOP.Solution;

import OOP.Provided.CasaDeBurrito;
import OOP.Provided.Profesor;
import java.util.*;
import java.util.stream.Collectors;

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
        this.rates = new HashMap<>();
    }

    public CasaDeBurritoImpl(CasaDeBurrito other)
    {
        this.id = other.getId();
        this.name = other.getName();
        this.dist = other.distance();
        this.menu = new HashSet<>(((CasaDeBurritoImpl) other).menu);
        this.rate_cnt = other.numberOfRates();
        this.rate_sum = ((CasaDeBurritoImpl) other).rate_sum;
        this.rates = new HashMap<>(((CasaDeBurritoImpl) other).rates);
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
        return this.rates.containsKey(p.getId());
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

        return "CasaDeBurrito: " +
                name +
                ".\n" +
                "Id: " +
                id +
                ".\n" +
                "Distance: " +
                this.dist +
                ".\n" +
                "Menu: " +
                menu
                        .stream()
                        .sorted()
                        .map(String::toString)
                        .collect(Collectors.joining(", ")) +
                ".";
    }

    @Override
    public int compareTo(CasaDeBurrito o) 
    {
        return Integer.compare(this.id, o.getId());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        CasaDeBurritoImpl that = (CasaDeBurritoImpl) o;
        return id == that.id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}