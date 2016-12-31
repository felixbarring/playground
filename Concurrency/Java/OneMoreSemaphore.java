

import java.util.concurrent.locks.*;

public class OneMoreSemaphore {

  private Lock lock = new ReentrantLock();
  private Condition queue = lock.newCondition();
  private int permits;
  private int counter = 0;
  
  OneMoreSemaphore(int p){
    permits = p;
  }
  
  public void acquire() throws InterruptedException{
    lock.lock();
    try {
      while(!(counter < permits)) queue.await();
      ++counter;
    } finally {
      lock.unlock();
    }
  }
  
  public void release(){
    lock.lock();
    try{
      if(counter > 0) --counter;
    } finally {
      lock.unlock();
    }
  }
  
}
