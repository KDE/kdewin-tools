// -*- c-basic-offset: 2 -*-
/*
 *  This file is part of the KDE libraries
 *  Copyright (C) 1999-2000 Harri Porten (porten@kde.org)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

// adapted to kdevelop by Roberto Raggi <roberto@kdevelop.org>

#include "lookup.h"

#include <QtDebug>

#include <stdio.h>
#include <string.h>

const HashEntry* Lookup::findEntry( const struct HashTable *table,
                              const QChar *c, unsigned int len )
{
  if (table->type != 2) {
    qDebug() << "Unknown hash table version";
    return 0;
  }
  char *ascii = new char[len+1];
  unsigned int i;
  for(i = 0; i < len; i++, c++) {
    if (!c->row())
      ascii[i] = c->cell();
    else
      break;
  }
  ascii[i] = '\0';

  int h = hash(ascii) % table->hashSize;
  const HashEntry *e = &table->entries[h];

  // empty bucket ?
  if (!e->s) {
    delete [] ascii;
    return 0;
  }

  do {
    // compare strings
    if (strcmp(ascii, e->s) == 0) {
      delete [] ascii;
      return e;
    }
    // try next bucket
    e = e->next;
  } while (e);

  delete [] ascii;
  return 0;
}

const HashEntry* Lookup::findEntry( const struct HashTable *table,
				    const QString &s )
{
    return findEntry( table, s.unicode(), s.length() );
}

int Lookup::find(const struct HashTable *table,
		 const QChar *c, unsigned int len)
{
  const HashEntry *entry = findEntry( table, c, len );
  if (entry)
    return entry->value;
  return -1;
}

int Lookup::find(const struct HashTable *table, const QString &s)
{
  return find(table, s.unicode(), s.length());
}

unsigned int Lookup::hash(const QChar *c, unsigned int len)
{
  unsigned int val = 0;
  // ignoring rower byte
  for (unsigned int i = 0; i < len; i++, c++)
    val += c->cell();

  return val;
}

unsigned int Lookup::hash(const QString &key)
{
    return hash(key.unicode(), key.length());
}

unsigned int Lookup::hash(const char *s)
{
  unsigned int val = 0;
  while (*s)
    val += *s++;

  return val;
}
