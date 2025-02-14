// import {
//   exists,
//   saveToPersistent,
//   saveFileToIDBFS,
//   timetableFileExists
// } from "../utl/IDBFSHelper.js";
import {
  getComponents,
  getTimetableComponents
} from "../utl/goldenLayoutHelper.js";

// import { Module } from "../soro-client.js";

function loadTimetableFromIDBFS(filePath, currentInfrastructure) {
  /* Loading from cache is very slow atm, so disabled
   const cachePath = new Module.FilesystemPath('/idbfs/cache/' + infrastructureFilename);
   if (exists(cachePath.string())) {
     this._current = new Module.Infrastructure(cachePath, true);
   } else {
   */

  const timetableOpts = new Module.TimetableOptions();
  timetableOpts.timetable_path = new Module.FilesystemPath(filePath);

  try {
    return new Module.Timetable(timetableOpts, currentInfrastructure);
  } catch (e) {
    console.error(e);
  }

  /* try {
     this._current.save(cachePath);
     saveToPersistent();
   } catch (e) {
     console.error("Could not write serialized cache, maybe compiled without SERIALIZE?");
     console.error(e);
   }
}
   */
}

export class TimetableManager {
  constructor() {
  }

  updateTimetableComponents() {
    for (const timetableComponent of getTimetableComponents()) {
      timetableComponent.changeTimetable(this._current);
    }
  }

  notifyComponents() {
    console.log("components", getComponents());
    for (const component of getComponents()) {
      component.changeTimetable && component.changeTimetable(this._current);
    }
  }

  get() {
    return this._current;
  }

  load(timetableFilename, currentInfrastructure) {
    if (!currentInfrastructure) {
      console.error("Tried loading a timetable with the currentInfrastructure undefined!");
      return;
    }

    let timetablePath = timetableFileExists(timetableFilename)

    if (timetablePath) {
      console.log("Reading", timetablePath, "from IDBFS.");
      this._current = loadTimetableFromIDBFS(timetablePath, currentInfrastructure)
      this.updateTimetableComponents();
    } else {
      console.log("Fetching", timetableFilename, "from server.");
      fetch(window.origin + '/timetable/' + timetableFilename)
        .then(response => response.arrayBuffer())
        .then(buf => saveFileToIDBFS(timetableFilename, buf))
        .then(filePath => this._current = loadTimetableFromIDBFS(filePath, currentInfrastructure))
        .then(_ => this.updateTimetableComponents())
        .catch(e => console.error(e));
    }


    this.updateTimetableComponents();
    this.notifyComponents();
  }

  unload() {
    this._current = undefined;
    this.updateTimetableComponents();
    this.notifyComponents();
  }

  addTimetableComponent() {
    window.goldenLayout.addComponent('TimetableComponent', {}, 'Timetable')
  }

  _current = undefined;
}