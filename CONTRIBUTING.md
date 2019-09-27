# How to contribute efficiently

Sections covered in this file:

* [Reporting bugs or proposing features](#reporting-bugs-or-proposing-features)
* [Contributing pull requests](#contributing-pull-requests)
* [Contributing with translations](#contributing-with-translation)
* [Code format](#code-format)

**Please read the first section before reporting a bug!**

## Reporting bugs or proposing features

Please, open just an issue per bug, and only a bug per issue. Don't open many
issues for the same bug, and don't report many bugs in the same issue. Same
for feature requests!

#### Specify the platform

Please, when opening an issue, specify the OS you are running Laigter on,
and if possible report the glsl version supported by your graphic card.

#### Specify steps to reproduce

If possible, add a description for reproducing this.

## Contributing pull requests

If you want to add new feature, please talk to me first on [discord](https://discord.gg/88kJqry),
twitter, by mail, or open an issue to propose the feature first.
And please provide a use case.

If you are planning to fix a bug, also ask me about the implementation.

Avoid using the same PR to fix/add multiple bugs/features. Try to do
a PR for each bug/feature. Also, if you have many commits, squash them
unless there is a reazon not to do so.

## Contributing with translation

The easiest way to contribute with translations, if you have Qt framework
installed, is to create a new laigter\_{locale-code}.ts file from the
laigter\_en.ts and open it with Qt linguist. If you don't have linguist,
just open another translation file (like laigter\_es.ts) and replace all
the text between `<translation><\translation>` tags to your language.

## Code format

*Note: the code does not respect this format right now, needs to be fixed*

For the code formatting we use clang-format. You can enable in Qt via
Beautifier plugin, or just use it's standalone version.

File names should be all lower case, sepparated with "\_" if needed.

Class names should be UpperCamelCase.

Function names should be lowerCamelCase. Signal and slots should use
the same format that Qt uses for them.

Variable names should use snake_case.

Others are not yet defined. If you need to define them, open an issue
and lets discuss about that!

Thanks!

Azagaya
