package OOP.Solution;

import java.util.*;

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
        profesors = new HashMap<Integer, Profesor>();
        casas = new HashMap<Integer, CasaDeBurrito>();
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
        Set<Profesor> result = new HashSet<Profesor>();
        for (Profesor profesor : profesors.values()) {
            Profesor profesorClone = new ProfesorImpl(profesor);
            result.add(profesorClone);
        }
        return result;
    }

    @Override
    public Collection<CasaDeBurrito> registeredCasasDeBurrito() 
    {
        Set<CasaDeBurrito> result = new HashSet<CasaDeBurrito>();
        for (CasaDeBurrito casa : casas.values()) {
            CasaDeBurrito casaClone = new CasaDeBurritoImpl(casa);
            result.add(casaClone);
        }
        return result;
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
        return this;
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByRating(Profesor p) throws ProfesorNotInSystemException 
    {
        if (!profesors.containsKey(p.getId()))
            throw new ProfesorNotInSystemException();
        
        ArrayList<Profesor> friends = new ArrayList<>(p.getFriends());
        friends.sort((a, b) -> a.compareTo(b));
        ArrayList<CasaDeBurrito> result = new ArrayList<>();
        for (Profesor profesor : friends) {
            if (!profesors.containsKey(profesor.getId())) continue;
            Collection<CasaDeBurrito> casasOfProfesor = profesor.favoritesByRating(0);
            for (CasaDeBurrito casa : casasOfProfesor) {
                if (result.contains(casa)) continue;
                result.add(casa);
            }
        }
        return result;
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByDist(Profesor p) throws ProfesorNotInSystemException 
    {
        if (!profesors.containsKey(p.getId()))
            throw new ProfesorNotInSystemException();
        
        ArrayList<Profesor> friends = new ArrayList<>(p.getFriends());
        friends.sort((a, b) -> a.compareTo(b));
        ArrayList<CasaDeBurrito> result = new ArrayList<>();
        for (Profesor profesor : friends) {
            if (!profesors.containsKey(profesor.getId())) continue;
            Collection<CasaDeBurrito> casasOfProfesor = profesor.favoritesByDist(Integer.MAX_VALUE);
            for (CasaDeBurrito casa : casasOfProfesor) {
                if (result.contains(casa)) continue;
                result.add(casa);
            }
        }
        return result;
    }

    @Override
    public boolean getRecommendation(Profesor p, CasaDeBurrito c, int t) throws ProfesorNotInSystemException,
            CasaDeBurritoNotInSystemException, CartelDeNachos.ImpossibleConnectionException 
    {
        return false;
    }

    @Override
    public List<Integer> getMostPopularRestaurantsIds() 
    {
        return null;
    }
    
}
