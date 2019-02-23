/*
   This file is part of the KDE project
   Copyright (C) 2007,2019 Ralf Habacker  <ralf.habacker@freenet.de>

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

   svg to png helper functions
*/

#include "helper.h"

#include <QtCore/QtDebug>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QProcess>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

#include <zlib.h>

bool verbose = false;
bool debug = false;

// vista support - requires a patched png2ico to support compressed png in ico container
// see http://www.axialis.com/tutorials/tutorial-vistaicons.html for details
#define VISTA_ICON_SUPPORT

#include <QSvgRenderer>
#include <QtGui/QImage>
#include <QtGui/QPainter>

bool unzipGZipFile(char *infile, char *outfile)
{
    gzFile file = gzopen(infile, "rb");
    FILE *out = fopen(outfile,"w");
    if (file == NULL) {
        return false;
    }
    char buf[1024];
    while (!gzeof(file)) {
        int len = gzread(file, buf, 1024);
        fwrite(buf,len,1,out);
    }
    gzclose(file);
    fclose(out);
    return true;
}

bool svg2png(const QString &inFile, const QString &outFile, int width, int height)
{
    QImage img(width, height, QImage::Format_ARGB32_Premultiplied);
    img.fill(0);

    QString svgFile = inFile;
    QString tmpFile;
    if (svgFile.endsWith(".svgz")) {
        QFileInfo iif(inFile);
        QFileInfo of(outFile);
        tmpFile = of.absolutePath()+'/'+iif.baseName()+".svg";
        bool ret = unzipGZipFile(svgFile.toLocal8Bit().data(),tmpFile.toLocal8Bit().data());
        if (verbose || !ret)
            qDebug() << "uncompressing" << svgFile << "to" << tmpFile << ":" << (ret ? "okay" : "error");

        if (!ret) {
            return false;
        }
        svgFile = tmpFile;
    }


    QSvgRenderer renderer(svgFile);

    if(renderer.isValid()) {
        QPainter p(&img);
        renderer.render(&p);
        img.save(outFile, "PNG");

        if (verbose)
            qDebug() << "converting" << svgFile << "to" << outFile;
    }
    if (!debug) {
        if (verbose)
            qDebug() << "deleting temporary file" << tmpFile;
        QFile::remove(tmpFile);
    }
    return true;
}
