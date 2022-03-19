package View;
import java.util.Scanner;

import Exceptions.RepoException;
import Model.*;
import Repository.Repo;
import Controller.Controller;

import javax.xml.transform.Source;

public class Main {

    public static void main(String[] args) {
        Repo repo = new Repo();
        Controller controller = new Controller(repo);

        try {
            controller.add(new Car("CPopescu343", 765));
            controller.add(new Car("CAlin423", 432));
            controller.add(new Car("CAlina313", 543));
            controller.add(new Truck("TMarius321", 543));
            controller.add(new Truck("TMarius3421", 1543));
            controller.add(new Truck("TMarius431", 2543));
            controller.add(new Car("CVasile433", 123));;
            controller.add(new MotorBike("MBMihail234", 43215));;
            controller.add(new MotorBike("MBVentora4311", 1243));;
            controller.add(new MotorBike("MBHercules4322", 12354));
            controller.add(new Truck("TGheorghe1322", 2583));
        }
        catch(RepoException e){
            System.out.println(e.toString());
        }
        menu(controller);
    }

    private static void printMainMenu() {
        System.out.println("\n-------------------");
        System.out.println("\n0. Exit ");
        System.out.println("1. Add ");
        System.out.println("2. Remove ");
        System.out.println("3. Show all vehicles");
        System.out.println("4. Filter vehicles with repair cost bigger than 1000 ");
        System.out.println("Give command: ");
    }

    private static void printVehicleTypes() {
        System.out.println("0. Exit ");
        System.out.println("1. Car ");
        System.out.println("2. Truck ");
        System.out.println("3. Motorbike");
    }

    public static void menu(Controller ctrl) {
        boolean b = true;

        while (b) {
            Main.printMainMenu();

            Scanner scanner = new Scanner(System.in);
            try {
                int cmd = scanner.nextInt();
                switch (cmd) {
                    case 0 -> b = false;
                    case 1 -> {
                        addVehicleMenu(ctrl);
                    }
                    case 2 -> deleteVehicleMenu(ctrl);
                    case 3 -> showAllVehiclesMenu(ctrl);
                    case 4 -> solveProblemMenu(ctrl);
                    default -> {
                        System.out.println("Wrong command number.");

                    }
                }
            } catch (RepoException e) {
                System.out.println(e.toString());
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }

        }
    }

    private static void solveProblemMenu(Controller ctrl) throws RepoException{
        Vehicle[] v = ctrl.filter(1000);

        for(int i = 0;i< v.length;i++){
            if(v[i]!= null)
                System.out.println(v[i]);
        }
    }

    private static void showAllVehiclesMenu(Controller ctrl) throws RepoException{
        System.out.println(ctrl.toString());
    }

    private static void deleteVehicleMenu(Controller ctrl) throws RepoException {
        boolean b = true;

        while (b) {

            Scanner scanner = new Scanner(System.in);
            try {

                System.out.println("Give name of vehicle to delete: ");
                String name = scanner.nextLine();

                ctrl.remove(name);

                System.out.println("Vehicle deleted successfully.");
            } catch (RepoException e) {
                System.out.println(e.toString());
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
            b=false;
        }
    }

    private static void addVehicleMenu(Controller ctrl) throws RepoException {
        boolean b = true;

        while (b) {
            Scanner scanner = new Scanner(System.in);
            try {
                System.out.println("Give name of vehicle: ");
                String name = scanner.nextLine();


                System.out.println("Give price of vehicle: ");
                int price = scanner.nextInt();
                scanner.nextLine();

                System.out.println("Select vehicle type: ");
                Main.printVehicleTypes();
                int cmd = scanner.nextInt();
                b=false;
                switch (cmd) {
                    case 0 -> b = false;
                    case 1 -> {
                        ctrl.add(new Car(name, price));
                        System.out.println("Car added successfully.");
                    }
                    case 2 -> {
                        ctrl.add(new Truck(name, price));
                        System.out.println("Truck added successfully.");
                    }
                    case 3 -> {
                        ctrl.add(new MotorBike(name, price));
                        System.out.println("Motorbike added successfully.");
                    }
                    default -> {
                        System.out.println("Wrong command number.");
                        b=true;
                    }
                }
            } catch (RepoException e) {
                System.out.println(e.toString());
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }

    }
}
