import Models.ADTs.*;
//import View.View;
public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world! :)");

        //View.startProgram();

    }

    public static void testADTs(){
        MyIDictionary<String, Integer> dic = new MyDictionary<String, Integer>();

        dic.put(new String("Haha"), 5);
        dic.put(new String("baba"), 8);
        dic.put(new String("das"), 9);
        dic.put(new String("fd"), 10);

        MyIList<String> list = new MyList<>();

        list.add("asd");
        list.add("rew");
        list.add("tre");

        MyIStack<String> stack  = new MyStack<String>();

        stack.push("ads");
        stack.push("tr");
        stack.push("dfs");
    }
}
