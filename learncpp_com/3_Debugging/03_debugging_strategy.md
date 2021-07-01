# A strategy for debugging

When debugging a program, in most cases the vast majority of your time will be spent trying to find where the error actually is. Once the issue is found, the remaining steps (fixing the issue and validating that the issue was fixed) are often trivial in comparison.

### Finding problems via code inspection

In most cases (especially in smaller programs), we can quickly home in on the proximity of where the issue is. However, as programs get more complex, finding issues by code inspection becomes more complex as well.

### Finding problems by running the program

We can watch the behavior of the program as it runs, and try to diagnose the issue from that. This approach can be generalized as:

1. Figure out how to reproduce the problem
1. Run the program and gather information to narrow down where the problem is
1. Repeat the prior step until you find the problem

#### Reproducing the problem

The first and most important step in finding a problem is to be able to reproduce the problem. The reason is it's extremely hard to find an issue unless you can observe it occurring.

If a software issue is blatant (e.g. the program crashes in the same place every time you run it). Then reproducing the problem can be trivial. However, sometimes reproducing an issue can be a lot more difficult. The problem may only occur on certain computers, or in particular circumstances (e.g. when the user enters certain input). In such cases, generating a set of reproduction steps can be helpful. 

**Reproduction steps** are a list of clear and precise steps that can be followed to cause an issue to recur with a high level of predictability. The goal is to be able to cause the issue to reoccur as much as possible, se we can run our program over and over and look for clues to determine what's causing the problem. If the issue can be reproduced 100% of the time, that's ideal, but less than 100% reproducibility can be okay. An issue that occurs only 50% of the time simply means it'll take twice as long to diagnose the issue, as half the time the program won't exhibit the problem and thus not contribute any useful diagnostic information.

#### Homing in on issues

Once we can reasonably reproduce the problem, the next step is to figure out where in the code the problem is. Based on the nature of the problem, this may be easy or difficult. 

Often, whatever it was that caused us to notice the problem will give us an initial guess that's close to where the acual problem is.
