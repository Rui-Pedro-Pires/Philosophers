# Philosophers Project - "I never thought philosophy would be so deadly"

## Project Overview
This project simulates the **Dining Philosophers Problem** using threads and mutexes (in the first version) and processes with semaphores (in the second version). The challenge was to ensure that philosophers can eat without conflicts and avoid starving by carefully managing shared resources (forks).

## Design and Development
### 1. **Threads and Mutexes**
Each philosopher is a thread, and each fork is protected by a mutex. Philosophers need to pick up two forks (left and right) to eat. Mutexes prevent two philosophers from using the same fork at the same time.

### 2. **State Management**
Philosophers cycle between three states: eating, sleeping, and thinking. I implemented time-based transitions between these states to simulate real-world behavior. If a philosopher doesn’t eat in time, they die, and the simulation stops.

### 3. **Avoiding Deadlocks**
To avoid situations where philosophers could lock up the system by holding one fork, I designed the program so that a philosopher either picks up both forks or releases the first one if the second isn’t available.

## Key Challenges
- **Race Conditions:** Solved using mutexes to protect shared resources (forks).
- **Deadlocks:** Handled by ensuring a philosopher always tries to pick up both forks at the same time.
- **Simultaneous Logging:** Used a mutex to prevent philosophers from writing to the log at the same time, ensuring clear output.

## Bonus Part
For the second version, I replaced threads with processes and used semaphores to manage the forks. Semaphores handle shared resources between processes, which required changes in how philosophers interact with the forks.

## Installation
1. Clone my repository:
   ```bash
   git clone git@github.com:Rui-Pedro-Pires/Philosophers.git
   ```
2. Navigate to the project directory:
   ```bash
   cd Philosophers
   ```

## How to Compile and Run

### Compilation
To compile the project:
```bash
make
```

### Running the Program
To run the program:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:
```bash
./philo 5 800 200 200
```

This runs a simulation with 5 philosophers where:
- Time to die = 800ms
- Time to eat = 200ms
- Time to sleep = 200ms
