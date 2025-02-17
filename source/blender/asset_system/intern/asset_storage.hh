/* SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup asset_system
 *
 * The database implementation for asset representations within a library. Not part of the public
 * API, storage access happens via the #AssetLibrary API.
 */

#pragma once

#include <memory>

#include "BLI_set.hh"

struct AssetMetaData;
struct ID;
struct IDRemapper;

namespace blender::asset_system {

class AssetRepresentation;

class AssetStorage {
  using StorageT = Set<std::unique_ptr<AssetRepresentation>>;

  StorageT external_assets_;
  /* Store local ID assets separately for efficient lookups.
   * TODO(Julian): A [ID *, asset] or even [ID.session_uuid, asset] map would be preferable for
   * faster lookups. Not possible until each asset is only represented once in the storage. */
  StorageT local_id_assets_;

 public:
  /** See #AssetLibrary::add_external_asset(). */
  AssetRepresentation &add_external_asset(StringRef name, std::unique_ptr<AssetMetaData> metadata);
  /** See #AssetLibrary::add_external_asset(). */
  AssetRepresentation &add_local_id_asset(ID &id);

  /** See #AssetLibrary::remove_asset(). */
  bool remove_asset(AssetRepresentation &asset);

  /** See #AssetLibrary::remap_ids_and_remove_nulled(). */
  void remap_ids_and_remove_invalid(const IDRemapper &mappings);
};

}  // namespace blender::asset_system
