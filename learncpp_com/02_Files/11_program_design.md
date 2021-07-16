# How to design your first programs

The most important thing to remember (and hardest thing to do) is to design your programs before you start coding. If you try to program before you have a good game-plan moving forward, you'll likely find that your code has a lot of problems, and you'll have to spend a lot of time fixing problems that could have been avoided altogether with a little thinking ahead.


### Design step 1: Define your goal

In order to write a successful program, you first need to define what your goal is. Ideally, you should be able to state this in a sentence or two. It is often useful to express this as a user-facing outcome.

### Design step 2: Define requirements

The next step is to think about requirements: the constraints that your solution needs to abide by (e.g. budge, timeline, space, memory, etc....), and the capabilities that the program must exhibit in order to meet the user's needs. Note that your requirements should similarly be focused on the "what", not the "how". A single problem may yield many requirements, and the solution isn't "done" until it satisfies all of them.

### Design step 3: Define your tools, targets, and backup plan

* Define what target architecture and/or OS your program will run on.
* Determine what set of tools you will be using.
* Determine whether you will write your program alone or as part of a team.
* Define your testing/feedback/release strategy.
* Determine how you will back up your code.

### Design step 4: Break hard problems down into easy problems

In real life, we often need to perform tasks that are very complex. Trying to figure out how to do these tasks can be very challenging. In such cases, we often make use of the **top down** method of problem solving. That is, instead of solving a single complex tasks, we break that task into multiple subtasks, each of which is individually easier to solve. If those subtasks are still too difficult to solve, they can be broken down further. By continuously splitting complex tasks into simpler ones, you can eventually get to a point where each individual task is manageable, if not trivial.

The other way to create a heirarchy of tasks is to do so from the bottom up. In this method, we start from a list of easy tasks, and construct the hierarchy by grouping them. 

Task hierarchies are extremely useful in programming, because once you have a task hierarchy, you have essentially defined the structure of your overall program. The top level task becomes main() because it is the main problem you are trying to solve. The subitems become functions in the program.

If it turns out that one of the items (functions) is too difficult to implement, simply split that item into multiple sub-items/sub-functions. Eventually you should reach a point where each function in your program is trivial to implement.

### Design step 5: Figure out the sequence of events

Determine how to link all the tasks together. The first step is to determine the sequence of events that will be performed.

At this point we are ready for implementation.

#### Implementation step 1: Outlining your main function

The above sequence can be used to outline your main program. Don't worry about the inputs and outputs for the time being.

` int main() `  
` { `  
` // Get first number from the user `  
` // getUserInput(); `  

` // Get mathematical operation from user `  
` getMathematicalOperation(); `  

` // Get second number from user `  
` // getUserInput(); `  

` // Calculate result `  
` // calculateResult(); `  

` // Print result `  
` // printResult(); `  

` return 0; `  
` } `  

#### Implementation step 2: Implement each function

In this step, for each function, you'll do three things:
1. Define the function prototype (inputs and outputs)
1. Write the function
1. Test the function

If your functions are granular enough, each functino should be fairly simple and straightforward. If a given function still seems overly-complex to implement, perhaps it needs to be broken down into subfunctions that can be more easily implemented (or it's possible you did something in the wrong order, and need to revisit your sequencing of events).

Don't implement your entire program in one go. Work on it in steps, testing each step along the way before proceeding.

#### Implementation step 3: Final testing

Once your program is finished, the last step is to test the whole program and ensure it works as intended. If it doesn't work, fix it.


## Words of advice when writing programs

**Keep your programs simple to start.** If you try to write something too complex to start, you will become overwhelmed and discouraged at your lack of progress. Instead, make your first goal as simple as possible.

**Add features over time.** Once you have your simple program working and working well, then you can add features to it. By adding each feature incrementally your program will get progressively more complex without overwhelming you in the process.

**Focus on one area at a time.** Don't try to code everything at once, and don't divide your attention across multiple tasks. Focus on one task at a time. If you split your attention, you are more likely to make mistakes and forget important details.

**Test each piece of code as you go.** 

**Don't invest in perfecting early code.** The first draft of a feature (or program) is rarely good. Furthermore, programs tend to evolve over time, as you add capabilities and find better ways to structure things. If you invest too early in polishing your code (adding lots of documentation, full compliance with best practices, making optimizations), you risk losing all of that investment when a code change is necessary. Instead, get your features minimally working and then move on. As you gain confidence in your solutions, apply successive layers of polish. Don't aim to perfect -- non-trivial programs are never perfect, and there's always something more that could be done to improve them. Get to good enough and move on.

For any non-trivial project, following these steps will definitely save you a lot of time in the long run. A little planning up front saves a lot of debugging at the end.
