package OOP.Provided;
import java.util.*;
import java.util.function.Predicate;

public class ProfesorImpl implements Profesor 
{
    private int id;
    private String name;
    private Set<Profesor> friends;
    private Set<CasaDeBurrito> favorites;
    

    public ProfesorImpl(int id, String name) {
        this.id = id;
        this.name = name;
        this.friends = new HashSet<Profesor>();
        this.favorites = new HashSet<CasaDeBurrito>();
    }

    public ProfesorImpl(Profesor other) {
        this.id = other.getId();
        this.name = ((ProfesorImpl) other).name;
        this.friends = other.getFriends();
        this.favorites = new HashSet<CasaDeBurrito>(other.favorites());
    }

    @Override
    public int getId() {
        return id;
    }

    @Override
    public Profesor favorite(CasaDeBurrito c)
            throws UnratedFavoriteCasaDeBurritoException
    {
        if (c.isRatedBy(this))
            this.favorites.add(c);
        else
            throw new UnratedFavoriteCasaDeBurritoException();
        return this;
    }

    @Override
    public Collection<CasaDeBurrito> favorites()
    {
        return new HashSet<CasaDeBurrito>(this.favorites);
    }

    @Override
    public Profesor addFriend(Profesor p) throws SameProfesorException, ConnectionAlreadyExistsException {
        if (this.id == p.getId())
            throw new SameProfesorException();
        if (this.friends.contains(p))
            throw new ConnectionAlreadyExistsException();
        friends.add(p);
        if(!(p.getFriends().contains(p)))
            p.addFriend(this);
        return this;
    }

    @Override
    public Set<Profesor> getFriends() 
    {
        return new HashSet<Profesor>(this.friends);
    }

    @Override
    public Set<Profesor> filteredFriends(Predicate<Profesor> p) {
        Set<Profesor> result = new HashSet<Profesor>();
        for (Profesor f : friends) 
        {
            if (p.test(f)) 
            {
                result.add(f);
            }
        }
        return result;
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByRating(int rLimit)
    {
        ArrayList<CasaDeBurrito> result = new ArrayList<CasaDeBurrito>();
        for (CasaDeBurrito favorite : favorites)
        {
            if (favorite.averageRating() >= rLimit)
                result.add(favorite);
        }
        result.sort(new CustomComparator());
        return result;
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByDist(int dLimit)
    {
        ArrayList<CasaDeBurrito> result = new ArrayList<CasaDeBurrito>();
        for (CasaDeBurrito favorite : favorites)
        {
            if (favorite.averageRating() <= dLimit)
                result.add(favorite);
        }
        result.sort(new CustomComparator());
        return result;
    }

    @Override
    public String toString() 
    {
        String str = "Profesor: " + this.name;
        str += "\nId: " + this.id;
        str += "\nFavorites: ";
        CasaDeBurrito[] favorites = (CasaDeBurrito[]) this.favorites.toArray();
        Arrays.sort(favorites);
        for (int i = 0; i < favorites.length; i++)
        {
            str += favorites[i].getName();
            if(i < favorites.length - 1)
                str += ", ";
            else
                str += ".";
        }
        return str;
    }

    @Override
    public int compareTo(Profesor o) 
    {
        if (this.id < o.getId())
            return -1;
        else if (this.id > o.getId())
            return 1;
        else
            return 0;
    }


    @Override
    public Collection<CasaDeBurrito> filterAndSortFavorites(Comparator<CasaDeBurrito> comp,
            Predicate<CasaDeBurrito> p) {
        ArrayList<CasaDeBurrito> result = new ArrayList<CasaDeBurrito>();
        for (CasaDeBurrito favorite : favorites)
        {
            if (p.test(favorite))
                result.add(favorite);
        }
        result.sort(comp);
        return result;
    }
    
    
}

class CustomComparator implements Comparator<CasaDeBurrito> {
    @Override
    public int compare(CasaDeBurrito o1, CasaDeBurrito o2) {
        if (o1.averageRating() > o2.averageRating())
            return 1;
        else if (o1.averageRating() < o2.averageRating())
            return -1;
        else
        {
            if (o1.distance() < o2.distance())
                return 1;
            else if (o1.distance() > o2.distance())
                return -1;
            else
            {
                if (o1.getId() < o2.getId())
                    return 1;
                else if (o1.getId() > o2.getId())
                    return -1;
                else return 0;
            }
        }
    }
}
