/*!
  \file NColorSettingBlock.qml
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import "../SettingBlockItems"
import "../nanairo.js" as Nanairo

NSettingBlock {
  id: color_setting_block

  readonly property int rgbMode: 0
  readonly property int spectraMode: 1
  property string keyPrefix: Nanairo.color
  property int viewMode: rgbMode
  property var currentItem: null
  property bool isItemChangeMode: false

  labelText: qsTr("Color")

  Rectangle {
    id: color_view

    anchors.horizontalCenter: color_setting_block.horizontalCenter
    y: color_setting_block.labelHeight + Nanairo.itemOffset
    width: Nanairo.defaultColorViewWidth
    height: Nanairo.defaultColorViewHeight
    color: color_setting_block.color

    readonly property int palette_offset: 2

    NButton {
      id: mode_change_button

      anchors.horizontalCenter: undefined
      anchors.verticalCenter: color_view.verticalCenter
      x: color_view.palette_offset
      y: 0
      width: 38
      backgroundColor: color_view.color

      text: (color_setting_block.viewMode == color_setting_block.rgbMode)
          ? qsTr("RGB")
          : qsTr("SPC")

      onClicked: {
        color_setting_block.flipViewMode();
      }
    }

    TabView {
      id: color_tab_view

      anchors.verticalCenter: color_view.verticalCenter
      x: (mode_change_button.x + mode_change_button.width) + color_view.palette_offset
      y: 0
      width: (color_view.width - color_view.palette_offset) - x
      height: mode_change_button.height

      style: TabViewStyle {
        tab: Rectangle {
          implicitWidth: 0
          implicitHeight: 0
        }
      }

      Tab {
        title: qsTr("RGB")
        active: true
        NRgbColorPalette {
          color: color_view.color
          keyPrefix: color_setting_block.keyPrefix
        }
      }

      Tab {
        title: qsTr("Spectra")
        active: true
        NSpectraFileView {
          color: color_view.color
          keyPrefix: color_setting_block.keyPrefix
        }
      }

      currentIndex: color_setting_block.viewMode
    }
  }

  onViewModeChanged: {
    if ((currentItem != null) && (!isItemChangeMode)) {
      // Color mode
      var mode = (viewMode == rgbMode) ? Nanairo.rgb
                                       : Nanairo.spectra;
      setCurrentItemValue(keyPrefix + Nanairo.colorMode, mode);
      // Color
      var colorTab = getColorTab(viewMode);
      colorTab.initializeItem(currentItem);
      colorTab.reflectItem();
    }
  }

  function flipViewMode() {
    viewMode = viewMode ^ 1;
  }

  function getColorTab(index) {
    return color_tab_view.getTab(index).item;
  }

  function initializeItem(item) {
    // Color mode
    item[keyPrefix + Nanairo.colorMode] = Nanairo.rgb;
    // 
    var colorTab = getColorTab(0);
    colorTab.initializeItem(item);
  }

  function reflectItem() {
    var item = currentItem;
    // Color mode
    var mode = item[keyPrefix + Nanairo.colorMode];
    switch (mode) {
      case Nanairo.rgb:
        viewMode = rgbMode;
        break;
      case Nanairo.spectra:
        viewMode = spectraMode;
        break;
      default:
        console.assert(false, "Unsupported color mode is specified: ", mode);
        break;
    }
    //
    var colorTab = getColorTab(viewMode);
    colorTab.reflectItem();
  }

  function setCurrentItem(item, itemChangeMode) {
    currentItem = item;
    isItemChangeMode = itemChangeMode;
    for (var i = 0; i < color_tab_view.count; ++i) {
      var colorTab = getColorTab(i);
      colorTab.setCurrentItem(item, itemChangeMode);
    }
  }

  function setCurrentItemValue(key, value) {
    if (currentItem != null) {
      currentItem[key] = value;
    }
  }

  function getItemData(item) {
    var mode = item[keyPrefix + Nanairo.colorMode];
    var colorTab = (mode == Nanairo.rgb) ? getColorTab(0)
                                     : getColorTab(1);
    var data = colorTab.getItemData(item);
    data[Nanairo.colorMode] = mode;

    var itemData = {};
    itemData[keyPrefix] = data;
    return itemData;
  }

  function makeItem(itemData) {
    var data = itemData[keyPrefix];
    var mode = data[Nanairo.colorMode];
    var colorTab = (mode == Nanairo.rgb) ? getColorTab(0)
                                     : getColorTab(1);
    var item = colorTab.makeItem(data);
    item[keyPrefix + Nanairo.colorMode] = mode;
    return item;
  }
}
