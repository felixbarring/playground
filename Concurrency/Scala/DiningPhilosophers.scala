

import java.util.concurrent.locks.{ Lock, ReentrantLock }

object DiningPhilosophers {
	def main(args: Array[String]) { new DiningPhilosophers }
}

class DiningPhilosophers {

	val forks = for (i <- 0 to 5) yield new ReentrantLock(true)
	val philosophers = for (i <- 0 to 5) yield new Philosopher(i, forks(i), forks(if (i == 5) 0 else i + 1))
	philosophers.foreach((p: Philosopher) => new Thread(p).start)

	class Philosopher(id: Int, left: ReentrantLock, right: ReentrantLock) extends Runnable {
		def think = Thread.sleep(2000)
		def eating = think

		def eat {
			left.lock
			right.lock
			println(id + " Eating")
			eating
			left.unlock
			right.unlock
		}

		def eat2 {
			right.lock
			left.lock
			println(id + " Eating")
			eating
			right.unlock
			left.unlock
		}

		def run {
			while (true) {
				think
				if (id == 5) eat2 else eat
			}
		}

	}

}