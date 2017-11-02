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
- Input integers variables (e.g., used for model selection) start with an "i" (e.g., `iverification`).
- Functions names are in Upper cases, with each word in Upper cases and no separation signs.
- Comments in the code with "///" are meant for inclusion in the Manual and should be collected at the beginning of every function.
- References to scientic literature should be added as comment in the code at **every** occurrence (e.g., values of parameters, equations...).

For example, a **good name** for a function evaluating the helium diffusion coefficient will be
`HeliumDiffusionCoefficient`, 



