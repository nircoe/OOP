package OOP.Solution;

import java.util.*;
import java.util.stream.Collectors;

import OOP.Provided.Profesor;
import OOP.Provided.Profesor.ProfesorAlreadyInSystemException;
import OOP.Provided.Profesor.ProfesorNotInSystemException;
import OOP.Provided.Profesor.SameProfesorException;
import OOP.Provided.Profesor.ConnectionAlreadyExistsException;
import OOP.Provided.CasaDeBurrito;
import OOP.Provided.CasaDeBurrito.CasaDeBurritoAlreadyInSystemException;
import OOP.Provided.CasaDeBurrito.CasaDeBurritoNotInSystemException;
import OOP.Provided.CartelDeNachos;

public class CartelDeNachosImpl implements CartelDeNachos
{
    private Map<Integer, Profesor> profesors;
    private Map<Integer, CasaDeBurrito> casas;

    public CartelDeNachosImpl()
    {
        profesors = new HashMap<>();
        casas = new HashMap<>();
    }

    @Override
    public Profesor joinCartel(int id, String name) throws ProfesorAlreadyInSystemException 
    {
        if (this.profesors.containsKey(id))
            throw new ProfesorAlreadyInSystemException();

        ProfesorImpl p = new ProfesorImpl(id, name);
        this.profesors.put(id, p);
        return p;
    }

    @Override
    public CasaDeBurrito addCasaDeBurrito(int id, String name, int dist, Set<String> menu)
            throws CasaDeBurritoAlreadyInSystemException
    {
        if (this.casas.containsKey(id))
            throw new CasaDeBurritoAlreadyInSystemException();

        CasaDeBurritoImpl c = new CasaDeBurritoImpl(id, name, dist, menu);
        this.casas.put(id, c);
        return c;
    }

    @Override
    public Collection<Profesor> registeredProfesores()
    {
        return profesors
                .values()
                .stream()
                .map(ProfesorImpl::new)
                .collect(Collectors.toSet());
    }

    @Override
    public Collection<CasaDeBurrito> registeredCasasDeBurrito() 
    {
        return casas
                .values()
                .stream()
                .map(CasaDeBurritoImpl::new)
                .collect(Collectors.toSet());
    }

    @Override
    public Profesor getProfesor(int id) throws ProfesorNotInSystemException
    {
        if (!profesors.containsKey(id))
            throw new ProfesorNotInSystemException();
        
        return profesors.get(id);
    }

    @Override
    public CasaDeBurrito getCasaDeBurrito(int id) throws CasaDeBurritoNotInSystemException 
    {
        if (!casas.containsKey(id))
            throw new CasaDeBurritoNotInSystemException();
        
        return casas.get(id);
    }

    @Override
    public CartelDeNachos addConnection(Profesor p1, Profesor p2)
            throws ProfesorNotInSystemException, ConnectionAlreadyExistsException, SameProfesorException 
    {
        if (!profesors.containsKey(p1.getId()) || !profesors.containsKey(p2.getId()))
            throw new ProfesorNotInSystemException();
        
        p1.addFriend(p2);
        p2.addFriend(p1);
        return this;
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByRating(Profesor p) throws ProfesorNotInSystemException 
    {
        if (!profesors.containsKey(p.getId()))
            throw new ProfesorNotInSystemException();

        return p.getFriends()
                .stream()
                .sorted()
                .filter(f -> profesors.containsKey(f.getId()))
                .flatMap(f -> f.favoritesByRating(0).stream())
                .distinct()
                .collect(Collectors.toList());
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByDist(Profesor p) throws ProfesorNotInSystemException 
    {
        if (!profesors.containsKey(p.getId()))
            throw new ProfesorNotInSystemException();

        return p.getFriends()
                .stream()
                .sorted()
                .filter(f -> profesors.containsKey(f.getId()))
                .flatMap(f -> f.favoritesByDist(Integer.MAX_VALUE).stream())
                .distinct()
                .collect(Collectors.toList());
    }

    private boolean[] getRecommendationAUX(Profesor p, CasaDeBurrito c, int t, Map<Integer, Profesor> m, int dist, boolean b)
    {
        Map<Integer, Profesor> copy = new HashMap<Integer, Profesor>(m);
        boolean[] r = new boolean[2];
        r[0] = true;
        r[1] = b;
        Set<Profesor> friends = p.getFriends();
        for (Profesor f : friends)
        {
            if(!(m.containsValue(f)))
            {
                if (f.favorites().contains(c))
                {
                    r[1] = false;
                    if(dist > t) {
                        r[0] = false;
                        return r;
                    }
                }
                for(Profesor friend: friends)
                {
                    m.putIfAbsent(friend.getId(), friend);
                }
                r = getRecommendationAUX(f, c, t, m, dist + 1, r[1]);
                m = copy;
                if(r[0] == false) return r;
            }
        }
        return r;
    }

    @Override
    public boolean getRecommendation(Profesor p, CasaDeBurrito c, int t) throws ProfesorNotInSystemException,
            CasaDeBurritoNotInSystemException, CartelDeNachos.ImpossibleConnectionException 
    {
        if (!(this.profesors.containsValue(p)))
            throw new ProfesorNotInSystemException();
        if (!(this.casas.containsValue(c)))
            throw new CasaDeBurritoNotInSystemException();
        if (t < 0)
            throw new ImpossibleConnectionException();
        Map<Integer, Profesor> m = new HashMap<Integer, Profesor>();
        m.put(p.getId(), p);
        boolean[] r = getRecommendationAUX(p, c, t, m, 1, true);
        if (r[1])
        {
            if (p.favorites().contains(c))
                return true;
            return false;
        }
        return r[0];
    }

    @Override
    public List<Integer> getMostPopularRestaurantsIds() 
    {
        if(this.casas.isEmpty() || this.profesors.isEmpty())
            return new ArrayList<Integer>();
        Map<Integer, Integer> scores = new HashMap<Integer, Integer>(); // id -> counter
        for (Integer id : this.casas.keySet())
        {
            scores.put(id, 0);
        }
        for (Profesor p : this.profesors.values())
        {
            for (Profesor f : p.getFriends()) {
                for (CasaDeBurrito c : f.favorites()) {
                    int casaId = c.getId();
                    int prevscore = scores.get(casaId);
                    scores.replace(casaId, prevscore + 1);
                }
            }
        }
        List<Integer> list = new ArrayList<Integer>();
        int max = (int)(scores.values().toArray())[0];
        for(Integer v: scores.values())
        {
            if (v > max)
                max = v;
        }
        for(Integer id: scores.keySet())
        {
            if(scores.get(id) == max)
                list.add(id);
        }
        return list.stream().sorted().toList();
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();

        str.append("Registered profesores: ");
        str.append(profesors
                .values()
                .stream()
                .sorted()
                .map(p -> String.valueOf(p.getId()))
                .collect(Collectors.joining(", ")));
        str.append(".\n");

        str.append("Registered casas de burrito: ");
        str.append(casas
                .values()
                .stream()
                .sorted()
                .map(c -> String.valueOf(c.getId()))
                .collect(Collectors.joining(", ")));
        str.append(".\n");

        str.append("Profesores:\n");
        profesors.keySet().forEach(id -> {
            str.append(id);
            str.append(" -> [");
            str.append(profesors
                    .get(id)
                    .getFriends()
                    .stream()
                    .sorted()
                    .map(p -> String.valueOf(p.getId()))
                    .collect(Collectors.joining(", ")));
            str.append("].\n");
        });
        str.append("End profesores.");

        return str.toString();
    }
}
