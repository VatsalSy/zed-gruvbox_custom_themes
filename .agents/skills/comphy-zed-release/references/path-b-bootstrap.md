# Path B Bootstrap For Renamed Package

Use this once, only while `comphy-crisp-themes` is missing from `zed-industries/extensions`.

## Goal

Add `comphy-crisp-themes` as a new package entry without touching `gruvbox-crisp-themes`.

## Steps

1. Prepare a working clone of the org fork of the extensions registry.
   - `git clone https://github.com/comphy-lab/extensions.git`
   - This must be a genuine GitHub fork of `zed-industries/extensions`. A
     standalone repository with the same contents cannot open a
     cross-repository pull request upstream: GitHub requires both sides to be
     in the same fork network. `VatsalSy/extensions` is such a standalone
     repository, is in active use for the basilisk-qcc extension, and must not
     be used here.
   - `cd extensions`
   - `git remote add upstream https://github.com/zed-industries/extensions.git`
   - `git fetch upstream`
   - `git checkout -b add-comphy-crisp-themes upstream/main`
2. Add the new submodule path.
   - `git submodule add https://github.com/comphy-lab/comphy-zed-themes.git extensions/comphy-crisp-themes`
3. Add a new `extensions.toml` section.
   - Add:
   - `[comphy-crisp-themes]`
   - `submodule = "extensions/comphy-crisp-themes"`
   - `version = "<value from extension.toml version>"`
4. Sort and validate registry metadata.
   - `pnpm install`
   - `pnpm sort-extensions`
5. Commit and open PR.
   - `git add .gitmodules extensions/comphy-crisp-themes extensions.toml`
   - `git commit -m "Add comphy-crisp-themes"`
   - `git push -u origin add-comphy-crisp-themes`
   - `gh pr create --repo zed-industries/extensions --base main --head comphy-lab:add-comphy-crisp-themes --title "Add comphy-crisp-themes" --body "Add renamed CoMPhy theme package as a new extension entry."`
6. After merge, run releases from `comphy-zed-themes` normally.
   - The tag-triggered workflow in this repository should then open update PRs for `comphy-crisp-themes`.

## Verification

1. `curl -fsSL https://raw.githubusercontent.com/zed-industries/extensions/main/extensions.toml | rg -n "^\[comphy-crisp-themes\]$|^\[gruvbox-crisp-themes\]$"`
2. Confirm both package IDs exist.
3. Confirm future release tags create PR titles like `Update comphy-crisp-themes to vX.Y.Z`.
