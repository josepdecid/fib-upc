package edu.upc.fib.sid.helpers;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class ReflectionUtils {
    public static Object invokeMethod(Object object, String methodName, Object... args) {
        try {
            Class<?> argsTypes[] = new Class<?>[args.length];
            for (int i = 0; i < argsTypes.length; ++i)
                argsTypes[i] = args[i].getClass();
            Method method = object.getClass().getMethod(methodName, argsTypes);
            return method.invoke(object, args);
        } catch (NoSuchMethodException | IllegalAccessException | InvocationTargetException e) {
            e.printStackTrace();
        } return object;
    }
}
