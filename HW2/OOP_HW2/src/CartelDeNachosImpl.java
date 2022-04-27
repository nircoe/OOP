import java.util.*;
import OOP.Provided.Profesor;
import OOP.Provided.ProfesorImpl;
import OOP.Provided.Profesor.*;
import OOP.Provided.CasaDeBurrito;
import OOP.Provided.CasaDeBurritoImpl;
import OOP.Provided.CasaDeBurrito.*;

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
        Collection<Profesor> value = this.profesors.values();
        Set<Profesor> c = new HashSet<Profesor>();
        for (Profesor p : value) 
            c.add(new Profesor(p));
        return c;
    }

    @Override
    public Collection<CasaDeBurrito> registeredCasasDeBurrito() 
    {
        return null;
    }

    @Override
    public Profesor getProfesor(int id) throws ProfesorNotInSystemException 
    {
        return null;
    }

    @Override
    public CasaDeBurrito getCasaDeBurrito(int id) throws CasaDeBurritoNotInSystemException 
    {
        return null;
    }

    @Override
    public CartelDeNachos addConnection(Profesor p1, Profesor p2)
            throws ProfesorNotInSystemException, ConnectionAlreadyExistsException, SameProfesorException 
    {
        return null;
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByRating(Profesor p) throws ProfesorNotInSystemException 
    {
        return null;
    }

    @Override
    public Collection<CasaDeBurrito> favoritesByDist(Profesor p) throws ProfesorNotInSystemException 
    {
        return null;
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
