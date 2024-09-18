
# ESP32 - Non-Volatile Storage (NVS)

## 1. How Does it Work?

1. Flash Memory
2. Uses a dedicated partition
3. Data is stored as key-value pairs
4. NVS supports namespaces to organize data


---
## 2. Writing to NVS

### Initializing NVS
```C
esp_err_t ret = nvs_flash_init();
if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
}
ESP_ERROR_CHECK(ret);
```
#### Explanation

Initializes the NVS partition:
```C
nvs_flash_init(); 
```

If the NVS partition is full or there is a version mismatch, you need to erase the memory and reinitialize it:
```C
nvs_flash_erase();
```

### Opening an NVS Handle
```C
nvs_handle_t my_handle;
esp_err_t err = nvs_open("storage", NVS_READWRITE, &my_handle);
if (err != ESP_OK)
{
    // Handle error
}
```
#### Explanation:
- ```nvs_open()``` opens a namespace "storage" in NVS
- ```NVS_READWRITE``` allows reading and writing
- The handle ```my_handle``` is used for subsequent operations

### Writing Data to NVS

For each data type, a specific function is used
##### For an Integer Value
```C
int32_t my_value = 42;
err = nvs_set_i32(my_handle, "my_key", my_value);
if (err != ESP_OK)
{
    // Handle error
}
```
##### For a String
```C
const char *my_string = "Hello World";
err = nvs_set_str(my_handle, "my_string_key", my_string);
if (err != ESP_OK)
{
    // Handle error
}
```

### Committing Changes
After modifying values, they must be committed to ensure they are saved to flash memory.
```C
err = nvs_commit(my_handle);
if (err != ESP_OK)
{
    // Handle error
}
```
### Closing the NVS Handle
After completing the writing operations, close the handle to free resources.
```C
nvs_close(my_handle);
```


---
## 3. Reading from NVS

To retrieve data from NVS:
1. Initialize NVS (if not already initialized)

2. Open the NVS handle (same namespace and key)
 
3. Read the data:
- For an Integer:
```C
int32_t my_value = 0;
err = nvs_get_i32(my_handle, "my_key", &my_value);
if (err == ESP_OK)
{
    // Use my_value
}
else if (err == ESP_ERR_NVS_NOT_FOUND)
{
    // Handle missing value
}
else
{
    // Handle other errors
}
```
- For a String:
```C
size_t required_size = 0; // Size of the string
err = nvs_get_str(my_handle, "my_string_key", NULL, &required_size);
if (err == ESP_OK && required_size > 0)
{
    char *my_string = malloc(required_size);
    err = nvs_get_str(my_handle, "my_string_key", my_string, &required_size);
    if (err == ESP_OK)
    {
        // Use my_string
    }
    free(my_string);
}
```

4. Close the NVS handle

---
## 4. Example: Storing Wi-Fi Credentials

To ensure the ESP32 reconnects to Wi-Fi after a restart, the credentials should be saved in NVS:
1. Initialize NVS (as described above)

2. Open the NVS handle
```c
nvs_handle_t wifi_handle;
err = nvs_open("wifi_config", NVS_READWRITE, &wifi_handle);
if (err != ESP_OK)
{
    // Handle error
}
```

3. Write the SSID and password
```c
const char *ssid = "MyWifiNetwork";
const char *password = "MyWifiPassword";

err = nvs_set_str(wifi_handle, "ssid", ssid);
if (err != ESP_OK) 
{
    // Handle error
}

err = nvs_set_str(wifi_handle, "password", password);
if (err != ESP_OK)
{
    // Handle error
}
```

4. Commit changes and close the handle
```c
err = nvs_commit(wifi_handle);
if (err != ESP_OK)
{
    // Handle error
}

nvs_close(wifi_handle);
```
