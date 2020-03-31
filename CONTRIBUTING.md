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

The following should be use:

* For **file names**: `snake_case` (example: `main.cpp`, `brush_interface.h`, `spin_box_slider2.qss`)

* For **class names**: `UpperCamelCase` (example: `ImageLoader`)

* For **class members**: `m_case` (example: `m_parallel_min`)

* For **class methods**: `UpperCamelCase` (example: `ImageLoader::LoadImage`)

* For **variables**: `snake_case` (example : `loaded_image`, `brush_size`)

* For **signals** and **slots**: `loweCamelCase` (example: `updateScene`)

* For **indentations**: use `2 spaces`

* For **class header**:
	```cpp
	class Name
	{
	//member variables first
	public: //same indentation as the class syntax
		int m_var;

	private:
		int m_var2;

	//methods
	public:
		Name();
		~Name();

	//other (protected, slots, etc etc)
	}
	```

* For **include**:
	```cpp
	//include files
	#include "filename.h"

	//include std lib
	#include <string>

	//include QT lib
	#include Qtxxxxx
	```

* For **statement codeblocks**:
	The same goes for `if`, `for`, `while`, and `function` blocks
	```cpp
	if (statement)
	{
	}
	else
	{
	}

	for (int i = 0; i <= 10; i++)
	{
	}

	void foo()
	{
	}
	```

* For **operators**:
	```cpp
	char assignment = 'a';
	int add = 1 + 1;
	int sub = 1 - 1;
	int mul = 1*1;
	int div = 1/1;
	```

* For **data types**:
	```cpp
	float a_float = 0.1f; //always put number(s) before the decimal point
	```

* For **switch statements**:
	```cpp
	switch (var)
	{
		case 1:
		{
			//do stuff here
			break;
		}
		case 2:
		{
			//do stuff here
			break;
		}
	}
	```

Others are not yet defined. If you need to define them, open an issue
and lets discuss about that!

Thanks!

Azagaya

