/*!
  \file NMaterialListItem.qml
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

import QtQuick 2.6
import QtQuick.Controls 1.5
import "../nanairo.js" as Nanairo

Rectangle {
  id: material_list_item

  property color backgroundColor

  width: Nanairo.materialListItemWidth
  height: Nanairo.materialListItemHeight
  color: (ListView.isCurrentItem)
      ? Qt.darker(backgroundColor, Nanairo.defaultDarkerScale)
      : (model.index % 2 == 0)
          ? backgroundColor
          : Qt.darker(backgroundColor, 1.05)

  Label {
    anchors.fill: parent

    text: model.name
    horizontalAlignment: Text.AlignLeft
    verticalAlignment: Text.AlignVCenter
    textFormat: Text.PlainText

    MouseArea {
      anchors.fill: parent
      onClicked: {
        material_list_item.ListView.view.currentIndex = model.index;
      }
    }
  }
}
