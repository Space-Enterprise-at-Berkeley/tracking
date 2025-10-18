# Setup Instructions
* Clone this repository.
* Within the repository, run git config --local include.path ../.gitconfig. This will add extra git commands for this repo.
* Run git submodule update --init --recursive.
* Within the repository, run git pull-all. This pulls the current branch as well as all submodules (the packet spec). Always use this instead of git pull, unless you aren't using the packet spec.
