# Instructions for committing new code in Sciantix

Open your terminal and type in the following instructions
```
git clone git@gitlab.com:<UserName>/sciantix.git
cd sciantix
git remote add upstream git@gitlab.com:poliminrg/sciantix.git
git pull –-rebase upstream master
```
Create issue on gitlab.com, then proceed with the following instructions
```
git checkout –b <BranchName_#IssueNumber>
git add <Files>
git commit –m "<CommitMessageEndingIn#IssueNumber>"
git pull –-rebase upstream master
git push origin <BranchName_#IssueNumber>
```
Create merge request gitlab.com.


In every moment, to check the status of your work type `git status`

# Syntax guidelines

In Sciantix we use some basic guidelines to help keeping an uniform syntaxing style among different contributions.

- Use **extensive names** for functions and variables. Do not be afraid of long names.
- Variables names are in lower cases, with words separated by "_" (e.g., `helium_diffusion_coefficient`).
- Global variables are in Upper cases, with words separated by "_" (e.g., `Helium_produced`).
- Input integer variables (e.g., used for model selection) start with an "i" (e.g., `iverification`).
- Flag integer variables start with an "f" (e.g., `fannealing`).
- Scaling factors variables start with "sf_" (e.g., `sf_helium_diffusion_coefficient`).
- Functions names are in Upper cases, with each word in Upper cases and no separation signs (e.g., `HeliumDiffusionCoefficient`).
- Files should have the same name as the function they contain.
- Comments in the code with "///" are meant for inclusion in the Manual and should be collected at the beginning of every function.
- Normal comments "//" should be used as much as possible.
- References to scientic literature should be added as comment in the code at **every** occurrence (e.g., values of parameters, equations...).

Thank for sticking as much as possible to these guidelines. We appreciate! :)




