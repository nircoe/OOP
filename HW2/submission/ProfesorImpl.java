package OOP.Solution;

import OOP.Provided.CasaDeBurrito;
import OOP.Provided.Profesor;
import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class ProfesorImpl implements Profesor
{
    private int id;
    private String name;
    private Set<Profesor> friends;
    private Set<CasaDeBurrito> favorites;
    

    public ProfesorImpl(int id, String name) {
        this.id = id;
        this.name = name;
        this.friends = new HashSet<>();
        this.favorites = new HashSet<>();
    }

    public ProfesorImpl(Profesor other) {
        this.id = other.getId();
        this.name = ((ProfesorImpl) other).name;
        this.friends = ((ProfesorImpl) other).friends;
        this.favorites = ((ProfesorImpl) other).favorites;
    }

    @Override
    public int getId() {
        return id;
    }

    @Override
    public Profesor favorite(CasaDeBurrito c)
            throws UnratedFavoriteCasaDeBurritoException
    {
        if (c.isRatedBy(this)) favorites.add(c);
        else throw new UnratedFavoriteCasaDeBurritoException();

        return this;
    }

    @Override
    public Collection<CasaDeBurrito> favorites()
    {
        return new HashSet<>(this.favorites);
    }

    @Override
    public Profesor addFriend(Profesor p) throws SameProfesorException, ConnectionAlreadyExistsException {
        if (id == p.getId()) throw new SameProfesorException();
        if (friends.contains(p)) throw new ConnectionAlreadyExistsException();

        friends.add(p);
        return this;
    }

    @Override
    public Set<Profesor> getFriends() 
    {
        return friends
                .stream()
                .map(ProfesorImpl::new)
                .collect(Collectors.toSet());
    }

    @Override
    public Set<Profesor> filteredFriends(Predicate<Profesor> p) {
        return friends
                .stream()
                .filter(p)
                .map(ProfesorImpl::new)
                .collect(Collectors.toSet());
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByRating(int rLimit)
    {
        return favorites
                .stream()
                .filter(c -> c.averageRating() >= rLimit)
                .sorted(new RatingComparator())
                .collect(Collectors.toList());
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByDist(int dLimit)
    {
        return favorites
                .stream()
                .filter(c -> c.distance() <= dLimit)
                .sorted(new DistanceComparator())
                .collect(Collectors.toList());
    }

    @Override
    public String toString() 
    {
        return "Profesor: " +
                name +
                ".\n" +
                "Id: " +
                id +
                ".\n" +
                "Favorites: " +
                favorites
                        .stream()
                        .sorted()
                        .map(CasaDeBurrito::getName)
                        .collect(Collectors.joining(", ")) +
                ".";
    }

    @Override
    public int compareTo(Profesor o) 
    {
        return Integer.compare(this.id, o.getId());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ProfesorImpl profesor = (ProfesorImpl) o;
        return id == profesor.id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public Collection<CasaDeBurrito> filterAndSortFavorites(Comparator<CasaDeBurrito> comp,
            Predicate<CasaDeBurrito> p) {
        return favorites
                .stream()
                .filter(p)
                .map(CasaDeBurritoImpl::new)
                .sorted(comp)
                .collect(Collectors.toList());
    }
}

class RatingComparator implements Comparator<CasaDeBurrito> {
    @Override
    public int compare(CasaDeBurrito o1, CasaDeBurrito o2) {
        if (o1.averageRating() < o2.averageRating())
            return 1;
        else if (o1.averageRating() > o2.averageRating())
            return -1;
        else
        {
            if (o1.distance() > o2.distance())
                return 1;
            else if (o1.distance() < o2.distance())
                return -1;
            else
            {
                return Integer.compare(o1.getId(), o2.getId());
            }
        }
    }
}

class DistanceComparator implements Comparator<CasaDeBurrito> {
    @Override
    public int compare(CasaDeBurrito o1, CasaDeBurrito o2) {
        if (o1.distance() > o2.distance())
            return 1;
        else if (o1.distance() < o2.distance())
            return -1;
        else
        {
            if (o1.averageRating() < o2.averageRating())
                return 1;
            else if (o1.averageRating() > o2.averageRating())
                return -1;
            else
            {
                return Integer.compare(o1.getId(), o2.getId());
            }
        }
    }
}
