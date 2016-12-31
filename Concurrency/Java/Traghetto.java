
import java.util.concurrent.Semaphore;

public class Traghetto {

  class Boat implements Runnable{

    final int NUMBER_OF_PASSENGERS = 3;
    Semaphore canBoard = new Semaphore(0);
    Semaphore boarded = new Semaphore(0);
    Semaphore arrived = new Semaphore(0);
    Semaphore left = new Semaphore(0);

    public void run(){
      try {
        while(true){
          canBoard.release(NUMBER_OF_PASSENGERS);
          System.out.println("Waiting for passengers to board");
          boarded.acquire(NUMBER_OF_PASSENGERS);
          System.out.println("The boat is moving 3 passengers");
          Thread.sleep(3000);
          arrived.release(NUMBER_OF_PASSENGERS);
          left.acquire(NUMBER_OF_PASSENGERS);
          System.out.println("The boat is moving back");
          Thread.sleep(3000);
        }
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
  
  class Passenger implements Runnable{
    
    Boat boat;
    
    Passenger(Boat boat){
      this.boat = boat;
    }
    
    public void run(){
      try {
        boat.canBoard.acquire(1);;
        boat.boarded.release(1);
        boat.arrived.acquire(1);
        boat.left.release(1);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }

  Traghetto(){
    Boat boat = new Boat();
    new Thread(boat).start();
    for(int i = 0; i < 4; i++){
      new Thread(new Passenger(boat)).start();
      new Thread(new Passenger(boat)).start();
      new Thread(new Passenger(boat)).start();
    }
  }

  public static void main(String[] args){
    new Traghetto();
  }

}
