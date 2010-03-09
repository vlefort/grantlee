/*
  This file is part of the Grantlee template system.

  Copyright (c) 2008 Stephen Kelly <steveire@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either version
  2 of the Licence, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library.  If not, see <http://www.gnu.org/licenses/>.

*/



#include "bbcodebuilder.h"

using namespace Grantlee;

BBCodeBuilder::BBCodeBuilder()
  : m_currentAlignment( Qt::AlignLeft )
{
}

BBCodeBuilder::~BBCodeBuilder()
{
}

void BBCodeBuilder::beginStrong()
{
  m_text.append( "[B]" );
}
void BBCodeBuilder::endStrong()
{
  m_text.append( "[/B]" );
}
void BBCodeBuilder::beginEmph()
{
  m_text.append( "[I]" );
}
void BBCodeBuilder::endEmph()
{
  m_text.append( "[/I]" );
}
void BBCodeBuilder::beginUnderline()
{
  m_text.append( "[U]" );
}
void BBCodeBuilder::endUnderline()
{
  m_text.append( "[/U]" );
}
void BBCodeBuilder::beginStrikeout()
{
  m_text.append( "[S]" );
}
void BBCodeBuilder::endStrikeout()
{
  m_text.append( "[/S]" );
}
void BBCodeBuilder::beginForeground( const QBrush &brush )
{
  m_text.append( QString( "[COLOR=%1]" ).arg( brush.color().name() ) );
}
void BBCodeBuilder::endForeground()
{
  m_text.append( "[/COLOR]" );
}

// Background colour not supported by BBCode.

void BBCodeBuilder::beginAnchor( const QString &href, const QString &name )
{
  m_text.append( QString( "[URL=%1]" ).arg( href ) );
}
void BBCodeBuilder::endAnchor()
{
  m_text.append( "[/URL]" );
}

// Font family not supported by BBCode.

void BBCodeBuilder::beginFontPointSize( int size )
{
  m_text.append( QString( "[SIZE=%1]" ).arg( QString::number( size ) ) );
}
void BBCodeBuilder::endFontPointSize()
{
  m_text.append( "[/SIZE]" );
}

void BBCodeBuilder::beginParagraph( Qt::Alignment a, qreal top, qreal bottom, qreal left, qreal right )
{
  Q_UNUSED( top );
  Q_UNUSED( bottom );
  Q_UNUSED( left );
  Q_UNUSED( right );
  if ( a & Qt::AlignRight ) {
    m_text.append( "\n[Right]" );
  } else if ( a & Qt::AlignHCenter ) {
    m_text.append( "\n[CENTER]" );
  }
  // LEFT is also supported in BBCode, but ignored.
  m_currentAlignment = a;
}

void BBCodeBuilder::endParagraph()
{
  if ( m_currentAlignment & Qt::AlignRight ) {
    m_text.append( "\n[/Right]\n" );
  } else if ( m_currentAlignment & Qt::AlignHCenter ) {
    m_text.append( "\n[/CENTER]\n" );
  } else {
    m_text.append( "\n" );
  }
  m_currentAlignment = Qt::AlignLeft;
}

void BBCodeBuilder::addNewline()
{
  m_text.append( "\n" );
}

void BBCodeBuilder::insertImage( const QString &src, qreal width, qreal height )
{
  Q_UNUSED( width );
  Q_UNUSED( height );
  m_text.append( QString( "[IMG]%1[/IMG]" ).arg( src ) );
}

void BBCodeBuilder::beginList( QTextListFormat::Style type )
{
  switch ( type ) {
  case QTextListFormat::ListDisc:
  case QTextListFormat::ListCircle:
  case QTextListFormat::ListSquare:
    m_text.append( "[LIST]\n" );  // Unordered lists are all disc type in BBCode.
    break;
  case QTextListFormat::ListDecimal:
    m_text.append( "[LIST=1]\n" );
    break;
  case QTextListFormat::ListLowerAlpha:
    m_text.append( "[LIST=a]\n" );
    break;
  case QTextListFormat::ListUpperAlpha:
    m_text.append( "[LIST=A]\n" );
    break;
  default:
    break;
  }
}

void BBCodeBuilder::endList()
{
  m_text.append( "[/LIST]\n" );
}

void BBCodeBuilder::beginListItem()
{
  m_text.append( "[*] " );
}

void BBCodeBuilder::beginSuperscript()
{
  m_text.append( "[SUP]" );
}

void BBCodeBuilder::endSuperscript()
{
  m_text.append( "[/SUP]" );
}

void BBCodeBuilder::beginSubscript()
{
  m_text.append( "[SUB]" );
}

void BBCodeBuilder::endSubscript()
{
  m_text.append( "[/SUB]" );
}


void BBCodeBuilder::beginTable( qreal, qreal, const QString & )
{
  m_text.append( "[TABLE]\n" );
}

void BBCodeBuilder::beginTableRow()
{
  m_text.append( "[/TABLE]" );
}

void BBCodeBuilder::appendLiteralText( const QString &text )
{
  m_text.append( escape( text ) );
}

const QString BBCodeBuilder::escape( const QString &s )
{
  if ( s.contains( "[" ) ) {
    return QString( "[NOPARSE]" + s + "[/NOPARSE]" );
  }
  return s;
}

QString& BBCodeBuilder::getResult()
{
  return m_text;
}

