# _**xpac**_ - **_A Cross-platform Package Manager_**

## Problem Statement:

A package manager is a standard program included on all unix-based operating systems. However, there is a lot of fragmentation among the different programs used, and the different protocols and methodologies employed by each one of them; for example, within Linux itself, one can find multiple package managers being employed based on the distribution in use; aptitude, dnf, yum, YAST, pacman, portage, Homebrew and many others are well known programs used by millions of people everyday. However, the existence of multiple programs to achieve the same goal and functionality leads to fragmentation, repeated effort, and inability to provide standardized support for different unix-based operating systems. We aim to solve this problem by developing a single do-it-all solution for package management across all standard unix-based operating systems, by leveraging the standardization of POSIX standards and developing an easy-to-use solution, which hopefully will someday become the standard for package managers.

## Objectives:

We aim to achieve the following objectives by creating xpac, a package manager with support for the following:

- Following basic operations across all unix based operating systems:
  - Installation
  - Updation
  - Deletion
- Ability to be cross-platform across all unix-based operating systems
- Ability to give the users a choice of going with the latest bleeding-edge packages, or opting for more stable versions
- Ability to compile from source in order to create a lean machine, or opt for pre-compiled binaries for more convenience, depending on the user's preferences
- Ability to detect the user's hardware and provide architecture specific packages
- Ability to compile packages in the event that pre-compiled binaries are not present, or if the user wishes to do so
- Create efficient algorithms in order to perform all of the above, and in doing so, create a rock-solid, stable package manager
