/*
 * Laigter: an automatic map generator for lighting effects.
 * Copyright (C) 2019  Pablo Ivan Fonovich
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * Contact: azagaya.games@gmail.com
 */

#ifndef WIN_INSTALL_H
#define WIN_INSTALL_H

#include <QString>

class QWidget;

/* Windows only. Laigter is distributed as a self extracting exe that unpacks
 * into a temporary folder and starts laigter from there, so the first thing it
 * does is ask where the user wants it. There is no separate installer, laigter
 * installs and uninstalls itself.
 *
 * Folders the user can write to are installed without asking for admin rights.
 * For the rest, like program files, laigter restarts itself elevated and that
 * copy does the install for every user. */
namespace WinInstall
{
enum class Mode
{
  Portable,  /* there is a portable.txt next to us */
  Installed, /* we are running from the installed folder */
  FirstRun   /* neither, so we are the temporary copy */
};

/* What the elevated copy is allowed to set up, as a command line number */
enum Extras
{
  Shortcut = 1,
  Association = 2,
  UninstallEntry = 4,
  DesktopShortcut = 8
};

Mode current_mode();

/* Asks where to put laigter and copies it there. setup_dir is where the self
 * extracting exe was run from, used as the default for a portable copy.
 * Returns true when laigter was copied and started from its new folder, so
 * this temporary instance must close. */
bool first_run(QWidget *parent = nullptr, const QString &setup_dir = QString());

/* The elevated copy of ourselves, installing where we could not */
bool install_for_all_users(const QString &dir, int extras);

/* Removes the shortcut, the file association and the installed folder.
 * Restarts elevated when the installed folder needs it. */
bool uninstall(QWidget *parent = nullptr, bool confirmed = false);
}

#endif // WIN_INSTALL_H
