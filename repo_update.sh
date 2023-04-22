#! /bin/bash

# A script to quickly create a branch, add a commit, and push it up.

#set -eo pipefail

current_branch=$(git rev-parse --abbrev-ref HEAD)

if [ "$current_branch" != master ] && [ "$current_branch" != main ]; then
  echo WARNING: YOU BRANCHED OF OFF "$current_branch", not main or master.
fi

if [ -z "$1" ]; then
  echo ERROR: Must have description
  exit 1
fi


description=$1                                                              # Fix duplication bug
kebab_name=$(echo "$description" | tr '[:upper:]' '[:lower:]' | tr ' ' '-') # fix-duplication-bug
commit_message="${description}"                            # ENG-123 Fix duplication bug

git checkout -- 
git add .
git status
git commit -m "$commit_message"
git push 
git pull
