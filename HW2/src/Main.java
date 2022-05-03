import OOP.Provided.CasaDeBurrito;
import OOP.Solution.CasaDeBurritoImpl;

import java.util.HashSet;
import java.util.Set;

public class Main {
    public static void main(String[] args)
    {
        Set<String> menu = new HashSet<String>() {{
            add("Humus");
            add("Tchina");
            add("Tubi");
        }};

        CasaDeBurrito CasaDeBurrito = new CasaDeBurritoImpl(1, "Pizza Place", 2, menu);
        // assertEquals(1, CasaDeBurrito.getId());
        // assertEquals(2, CasaDeBurrito.distance());

        System.out.println(CasaDeBurrito.getId());
        System.out.println(CasaDeBurrito.distance());

    }
}