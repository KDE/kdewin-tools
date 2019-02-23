/*
   This file is part of the KDE project
   Copyright (C) 2019 Ralf Habacker  <ralf.habacker@freenet.de>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.

   svg to multi png converter used to create app icons
*/

#include <QApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QProcess>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "../lib/helper.h"

int main(int argc, char **argv)
{
    if(argc < 3) {
        qDebug() << "Usage : svg2multipng <options> <svgfile> <pngfile-with-%1-pattern>";
        qDebug() << "options: --verbose print execution details";
        qDebug() << "         --debug   print debugging information e.g. do not delete temporary files";
        return -1;
    }
    int i = 1;
    if (QString(argv[i]) == "--verbose") {
        verbose = true;
        i++;
    }
    else if (QString(argv[i]) == "--debug") {
        debug = true;
        i++;
    }

    QApplication app(argc, argv);

    QString svgFile = QString::fromLocal8Bit(argv[i++]);
    QString pngFile = QString::fromLocal8Bit(argv[i++]);
    if (!pngFile.contains("%1")) {
        qDebug() << "output file name must have '%1' pattern";
        return 1;
    }

    if ( !svg2png(svgFile, pngFile.arg("16"),16,16) )
        return 1;
    if ( !svg2png(svgFile, pngFile.arg("22"),22,22) )
        return 1;
    if ( !svg2png(svgFile, pngFile.arg("32"),32,32) )
        return 1;
    if ( !svg2png(svgFile, pngFile.arg("48"),48,48) )
        return 1;
    if ( !svg2png(svgFile, pngFile.arg("64"),64,64) )
        return 1;
    if ( !svg2png(svgFile, pngFile.arg("128"),128,128) )
        return 1;

    return 0;
}
