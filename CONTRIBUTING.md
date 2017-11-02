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
