/*****************************************************************************
* Copyright 2015-2016 Alexander Barthel albar965@mailbox.org
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
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "fs/writer/ap/apronlightwriter.h"
#include "fs/writer/datawriter.h"
#include "fs/bgl/util.h"
#include "fs/bglreaderoptions.h"
#include "fs/writer/ap/airportwriter.h"
#include "fs/bgl/ap/rw/runway.h"

namespace atools {
namespace fs {
namespace writer {

using atools::fs::bgl::ApronLight;
using atools::fs::bgl::Runway;
using atools::sql::SqlQuery;

void ApronLightWriter::writeObject(const atools::fs::bgl::ApronLight *type)
{
  if(getOptions().isVerbose())
    qDebug() << "Writing ApronLight for airport "
             << getDataWriter().getAirportWriter()->getCurrentAirportIdent();

  bind(":apron_light_id", getNextId());
  bind(":airport_id", getDataWriter().getAirportWriter()->getCurrentId());

  // TODO create a WKT line from the edges
  QStringList list;
  for(const bgl::BglPosition& pos : type->getVertices())
    list.push_back(QString::number(pos.getLonX()) + " " + QString::number(pos.getLatY()));
  bind(":vertices", list.join(", "));

  list.clear();
  for(int i : type->getEdges())
    list.push_back(QString::number(i));
  bind(":edges", list.join(", "));

  executeStatement();
}

} // namespace writer
} // namespace fs
} // namespace atools