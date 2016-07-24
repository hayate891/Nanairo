/*!
  \file cui_renderer_manager.cpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#include "cui_renderer_manager.hpp"
// Standard C++ library
#include <string>
#include <tuple>
// Qt
#include <QDate>
#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QString>
#include <QTime>
#include <QTextStream>
#include <QtGlobal>
// Zisc
#include "zisc/error.hpp"
#include "zisc/stopwatch.hpp"
// Nanairo
#include "NanairoCommon/keyword.hpp"
#include "NanairoCore/Utility/scene_value.hpp"
#include "NanairoRenderer/cpu_scene_renderer.hpp"
#include "NanairoRenderer/renderer_parameter.hpp"
#include "NanairoRenderer/renderer_utility.hpp"
#include "NanairoRenderer/scene_document.hpp"
#include "NanairoRenderer/scene_renderer_base.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
CuiRendererManager::CuiRendererManager(const RendererParameter& parameters) noexcept
    : is_runnable_{false}
{
  initialize(parameters);
}

/*!
  \details
  No detailed.
  */
void CuiRendererManager::invokeRenderer() noexcept
{
  // Make a output directory
  const auto r = generateOutputDir();
  const bool result = std::get<0>(r);
  const auto& output_dir = std::get<1>(r);
  if (!result) {
    auto message = "Making the output dir: \"" + output_dir + "\" failed.";
    qFatal("%s", message.toStdString().c_str());
  }

  // Save a backup of scene settings
  QString message;
  const auto scene_file_path = output_dir + "/" + keyword::sceneBackupFileName;
  if (!SceneDocument::saveDocument(scene_file_path, settings_, message)) {
    qFatal("%s", message.toStdString().c_str());
  }

  // Load the scene settings
//  QScopedPointer<SceneSettings> settings{new SceneSettings};
//  settings->open(scene_file_path_);

  // Make output directory
//  const auto current_dir = QDir::current();
//  const auto key = QString{keyword::system} + "/" + keyword::sceneName;
//  const auto scene_name = settings->stringValue(key);
//  const auto current_time = getCurrentTime();
//  const auto dir_name = scene_name + "_" + current_time;
//  current_dir.mkdir(dir_name);
//
//  // Set the output path
//  const auto current_path = current_dir.absolutePath();
//  const auto output_dir = current_path + "/" + dir_name;
//
//  // Make the renderer
//  QScopedPointer<SceneRendererBase> renderer{new CpuSceneRenderer};
//  setRenderer(renderer.data());

  // Render
  renderer_->initialize(settings_);
  renderer_->renderImage(output_dir);
}

/*!
  */
bool CuiRendererManager::isRunnable() const noexcept
{
  return is_runnable_;
}

/*!
  */
std::tuple<bool, QString> CuiRendererManager::generateOutputDir() const noexcept
{
  const auto current_dir = QDir::current();
  const auto scene_settings = objectValue(settings_, keyword::scene);
  const auto scene_name = stringValue(scene_settings, keyword::sceneName);
  const auto current_time = getCurrentTime();
  const auto dir_name = scene_name + "_" + current_time;
  const bool result = current_dir.mkdir(dir_name);
  const auto output_dir = current_dir.absolutePath() + "/" + dir_name;
  return std::make_tuple(result, output_dir);
}

/*!
  \details
  No detailed.
  */
QString CuiRendererManager::getCurrentTime() const noexcept
{
  const auto current_date = QDate::currentDate().toString("yyyy_MM_dd");
  const auto current_time = QTime::currentTime().toString("HH_mm_ss");
  return current_date + "_" + current_time;
}

/*!
  \details
  No detailed.
  */
void CuiRendererManager::initialize(const RendererParameter& parameters) noexcept
{
  is_runnable_ = false;

  // Load a scene settings
  QString message;
  if (!SceneDocument::loadDocument(parameters.sceneFilePath(), settings_, message)) {
    qFatal("%s", message.toStdString().c_str());
  }

  // Renderer
  renderer_.reset(new CpuSceneRenderer);
  setRenderer();

  is_runnable_ = true;
}

/*!
  \details
  No detailed.
  */
void CuiRendererManager::setRenderer() noexcept
{
  auto renderer = renderer_.data();
  QSharedPointer<QTextStream> cout{new QTextStream{stdout}};

  auto output_rendering_info = [cout](const quint64 cycle, const qint64 time)
  {
    using zisc::cast;
    constexpr quint64 k = cast<quint64>(zisc::Stopwatch::Clock::period::den);
    const double fps = cast<double>(k * cycle) / cast<double>(time);
    const auto fps_string = QString::number(fps, 'f', 2);
    const auto cycle_string = QStringLiteral("%1").arg(cycle, 8, 10, QChar('0'));
    const auto time_string = getTimeString(zisc::Stopwatch::Clock::duration{time});

    *cout << "FPS: " << fps_string
          << " cycle: " << cycle_string 
          << " time: " << time_string << "\r";
    flush(*cout);
  };
  QObject::connect(renderer, &SceneRendererBase::updated, output_rendering_info);

  auto output_message = [cout](const QString& message)
  {
    *cout << message;
    endl(*cout);
  };
  QObject::connect(renderer, &SceneRendererBase::outputMessage, output_message);
}

} // namespace nanairo
