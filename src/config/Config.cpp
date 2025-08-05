#include "config/Config.h"

template <typename TRef>
bool saveConfigFile(const char *location, const char *filename, size_t size, const char *config_type, TRef &ref)
{
  JsonDocument doc;
  JsonObject root = doc.to<JsonObject>();

  ref.get(root);

  if (strcmp("flash", location) == 0)
  {
    File configFile = LittleFS.open(filename, "w");
    if (!configFile)
    {
      Serial.printf("Failed to create %s file for writing", filename);
      return false;
    }

    serializeJson(root, configFile);
  }
//   else if (strcmp("nvs", location) == 0)
//   {
//     std::string conf;
//     serializeJson(root, conf);
//     NVS.setString(config_type, conf);
//   }
  else
  {
    return false;
  }
  Serial.printf("%s config saved on %s", config_type, location);
  return true;
}

template <typename TRef>
bool loadConfigFile(const char *location, const char *nvs_backup_key, const char *filename, size_t size, const char *config_type, TRef &ref)
{
  if (strcmp("flash", location) == 0)
  {

    if (!LittleFS.exists(filename))
    {
    //   Serial.printf("loadConfigFile %s:%d", nvs_backup_key, static_cast<uint8_t>(NVS.getInt(nvs_backup_key)));
    //   if (NVS.getInt(nvs_backup_key) == 1)
    //   {
    //     NVS.setInt(nvs_backup_key, static_cast<uint8_t>(0));
    //     Serial.printf("Setup: loading %s config from nvs backup", config_type);
    //     loadConfigFile("nvs", nvs_backup_key, filename, size, config_type, ref);
    //   }
    //   else
    //   {
        Serial.printf("Setup: writing initial %s config", config_type);
    //   }
      if (!saveConfigFile(location, filename, size, config_type, ref))
      {
        return false;
      }
    }

    File configFile = LittleFS.open(filename, "r");
    if (!configFile)
    {
      Serial.printf("Failed to open %s file", config_type);
      return false;
    }

    size_t filesize = configFile.size();
    if (filesize > size)
    {
      Serial.printf("%s config file size is too large", config_type);
      return false;
    }

    JsonDocument root;
    DeserializationError error = deserializeJson(root, configFile);
    if (error)
      return false;

    ref.configLoaded = ref.set(root.as<JsonObject>());

    if (!ref.configLoaded)
    {
      Serial.printf("%s config version mismatch, resetting config...", config_type);
      saveConfigFile(location, filename, size, config_type, ref);
      delay(1000);
      ESP.restart();
    }

    Serial.printf("Setup: %s config loaded successful from %s", config_type, location);
  }
//   else if (strcmp("nvs", location) == 0)
//   {
//     std::string conf = NVS.getstring(config_type);
//     if (conf.empty())
//       return false;

//     JsonDocument root;
//     DeserializationError error = deserializeJson(root, conf);
//     if (error)
//       return false;

//     ref.set(root.as<JsonObject>());
//   }
  else
  {
    return false;
  }

  return true;
}

bool resetConfigFile(const char *filename)
{
  if (!LittleFS.remove(filename))
  {
    return false;
  }
  if (!LittleFS.exists(filename))
  {
    return true;
  }
  return false;
}

// bool loadWifiConfig(const char *location)
// {
//   return loadConfigFile(location, "usewificonfb", "/wifi.json", 2048, "wificonfig", wifiConfig);
// }

// bool saveWifiConfig(const char *location)
// {
//   return saveConfigFile(location, "/wifi.json", 2048, "wificonfig", wifiConfig);
// }

// bool resetWifiConfig()
// {
//   return resetConfigFile("/wifi.json");
// }

// bool loadSystemConfig(const char *location)
// {
//   return loadConfigFile(location, "usesysconfb", "/config.json", 4096, "systemconfig", systemConfig);
// }

// bool saveSystemConfig(const char *location)
// {
//   return saveConfigFile(location, "/config.json", 4096, "systemconfig", systemConfig);
// }

// bool resetSystemConfig()
// {
//   return resetConfigFile("/config.json");
// }

// bool loadLogConfig(const char *location)
// {
//   return loadConfigFile(location, "uselogconfb", "/syslog.json", 2048, "logconfig", logConfig);
// }

// bool saveLogConfig(const char *location)
// {
//   return saveConfigFile(location, "/syslog.json", 2048, "logconfig", logConfig);
// }

// bool resetLogConfig()
// {
//   return resetConfigFile("/syslog.json");
// }

// bool loadHADiscConfig(const char *location)
// {
//   return loadConfigFile(location, "usehsdiscconfb", "/hadisc.json", 8192, "hadiscconfig", haDiscConfig);
// }

// bool saveHADiscConfig(const char *location)
// {
//   return saveConfigFile(location, "/hadisc.json", 8192, "hadiscconfig", haDiscConfig);
// }

// bool resetHADiscConfig()
// {
//   return resetConfigFile("/hadisc.json");
// }

// bool saveSystemConfigs()
// {
//   bool res = false;
//   res = saveSystemConfig("flash");
//   res = saveLogConfig("flash");
//   res = saveHADiscConfig("flash");
//   res = saveRemotesConfig("flash");
//   res = saveVirtualRemotesConfig("flash");
//   return res;
// }

// bool resetSystemConfigs()
// {
//   bool res = false;
//   res = resetConfigFile("/config.json");
//   res = resetConfigFile("/syslog.json");
//   res = resetConfigFile("/hadisc.json");
//   res = resetConfigFile("/remotes.json");
//   res = resetConfigFile("/vremotes.json");
//   return res;
// }

// template <typename TDst>
// uint16_t serializeRemotes(const char *filename, const IthoRemote &remotes, TDst &dst)
// {
//   JsonDocument doc;

//   JsonObject root = doc.to<JsonObject>();

//   std::string tempStr = filename;
//   if (tempStr.find(".json") == std::string::npos)
//     return 0;

//   std::string rootName = tempStr.substr(1, static_cast<char>(tempStr.find(".json")));
//   remotes.get(root, rootName.c_str());

//   return serializeJson(doc, dst);
// }

// bool saveRemotesConfig(const char *location)
// {
//   return saveFileRemotes(location, "/remotes.json", "remotesconfig", remotes);
// }

// bool saveVirtualRemotesConfig(const char *location)
// {
//   return saveFileRemotes(location, "/vremotes.json", "vremotesconfig", virtualRemotes);
// }

// bool saveFileRemotes(const char *location, const char *filename, const char *config_type, const IthoRemote &remotes)
// {

//   if (strcmp("flash", location) == 0)
//   {
//     File configFile = LittleFS.open(filename, "w");
//     if (!configFile)
//     {
//       Serial.printf("Failed to create %s file", filename);
//       return false;
//     }
//     serializeRemotes(filename, remotes, configFile);
//   }
//   else if (strcmp("nvs", location) == 0)
//   {
//     std::string conf;
//     serializeRemotes(filename, remotes, conf);
//     NVS.setString(config_type, conf);
//   }

//   Serial.printf("Config %s saved on %s", filename, location);
//   return true;
// }

// template <typename TDst>
// bool deserializeRemotes(const char *filename, const char *config_type, TDst &src, IthoRemote &remotes)
// {

//   JsonDocument doc;

//   DeserializationError err = deserializeJson(doc, src);
//   if (err)
//   {
//     Serial.printf("Failed to deserialize remotes config %s", filename);
//     return false;
//   }

//   doc.shrinkToFit();

//   std::string tempStr = filename;
//   if (tempStr.find(".json") == std::string::npos)
//     return false;

//   std::string rootName = tempStr.substr(1, static_cast<char>(tempStr.find(".json")));

//   remotes.configLoaded = remotes.set(doc.as<JsonObject>(), rootName.c_str());
//   if (!remotes.configLoaded)
//   {
//     Serial.printf("Remotes config version mismatch, resetting config...");
//     saveFileRemotes("flash", filename, config_type, remotes);
//     delay(1000);
//     ESP.restart();
//   }

//   return true;
// }

// bool loadRemotesConfig(const char *location)
// {
//   return loadFileRemotes(location, "/remotes.json", "remotesconfig", "useremconfb", remotes);
// }

// bool loadVirtualRemotesConfig(const char *location)
// {
//   return loadFileRemotes(location, "/vremotes.json", "vremotesconfig", "usevremconfb", virtualRemotes);
// }

// bool loadFileRemotes(const char *location, const char *filename, const char *config_type, const char *nvs_backup_key, IthoRemote &remotes)
// {
//   if (strcmp("flash", location) == 0)
//   {
//     if (!LittleFS.exists(filename))
//     {
//       if (NVS.getInt(nvs_backup_key) == 1)
//       {
//         NVS.setInt(nvs_backup_key, static_cast<uint8_t>(0));
//         loadFileRemotes("nvs", filename, config_type, nvs_backup_key, remotes);
//       }
//       else
//       {
//         Serial.printf("Setup: writing initial %s config", config_type);
//       }
//       if (!saveFileRemotes("flash", filename, config_type, remotes))
//       {
//         return false;
//       }
//     }

//     File configFile = LittleFS.open(filename, "r");
//     if (!configFile)
//     {
//       Serial.printf("Setup: failed to open %s config file", config_type);
//       return false;
//     }

//     size_t size = configFile.size();
//     if (size > 4000)
//     {
//       Serial.printf("Setup: %s config file size is too large", config_type);
//       return false;
//     }

//     bool success = deserializeRemotes(filename, config_type, configFile, remotes);

//     if (!success)
//     {
//       Serial.printf("Failed to deserialize %s configuration from %s", config_type, location);
//       return false;
//     }
//   }
//   else if (strcmp("nvs", location) == 0)
//   {
//     std::string conf = NVS.getstring(config_type);
//     if (conf.empty())
//       return false;

//     bool success = deserializeRemotes(filename, config_type, conf, remotes);

//     if (!success)
//     {
//       Serial.printf("Failed to deserialize %s configuration from %s", config_type, location);
//       return false;
//     }
//   }
//   else
//   {
//     return false;
//   }

//   Serial.printf("Setup: %s config loaded successful from %s", config_type, location);
//   return true;
// }
