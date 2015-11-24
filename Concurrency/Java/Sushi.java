
import java.util.concurrent.Semaphore;

public class Sushi {

  class SushiMaster implements Runnable{
    Semaphore barIsOpen = new Semaphore(0);
    Semaphore barFreeSlots = new Semaphore(8);
    Semaphore barUsedSlots = new Semaphore(0);

    public void run(){
      System.out.println("The master is preparing");
      try {
        Thread.sleep(4000);
        barIsOpen.release(1);
        while(true){
          barFreeSlots.acquire(1);
          System.out.println("The master is making sushi");
          Thread.sleep(500);
          barUsedSlots.release(1);
        }
      } catch (InterruptedException e) { e.printStackTrace(); }
    }
  }

  class Customer implements Runnable{
    SushiMaster master;
    
    Customer(SushiMaster master){
      this.master = master; 
    }

    public void run(){
      System.out.println("Customer is entering the building");
      try {
        master.barIsOpen.acquire();
        master.barIsOpen.release();
        System.out.println("Customer is wainting for food");
        master.barUsedSlots.acquire(1);
        master.barFreeSlots.release(1);
        System.out.println("Customer is eating");
        Thread.sleep(2000);
        System.out.println("Customer is leaving");
      } catch (InterruptedException e) {     e.printStackTrace();     }
    }
  }

  Sushi(){
    SushiMaster master = new SushiMaster();
    for(int i = 0; i < 30; i++){
      new Thread(new Customer(master)).start();
    }
    new Thread(master).start();
  }

  public static void main(String[] args){
    new Sushi();
  }

}
