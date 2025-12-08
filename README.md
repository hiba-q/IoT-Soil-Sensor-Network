# 🌿 IoT‑Based Soil Sensor Network for Real‑Time Anomaly Detection

An Arduino + ThingSpeak integrated IoT system for monitoring **soil pH** and **CO₂ levels** in real time, designed to optimize greenhouse farming and enable early anomaly detection.

---

## 🧩 Overview

Monitoring **soil pH** and **CO₂** is crucial for maintaining optimal plant growth in controlled greenhouses.  
This project implements a real‑time network of IoT sensors connected to the **ThingSpeak cloud platform** for continuous monitoring, anomaly detection, and automated alerts.

**Built with:**
- **Arduino Uno** (simulated in Tinkercad)
- **pH Probe (A0)** and **CO₂ Sensor (A1)**
- **Wi‑Fi Module (D2/D3)** for wireless data transmission  
  *(Note: the Wi‑Fi module is no longer officially supported in Tinkercad due to security restrictions, but conceptually the design remains valid.)*
- **ThingSpeak Cloud** for data visualization and analytics

---

## ⚙️ Sensor Configuration

| Parameter | Normal Range | Alert Threshold |
|------------|---------------|----------------|
| pH | 5.5 – 7.0 | < 5.0 or > 7.5 |
| CO₂ | 500 – 1500 ppm | < 300 or > 1800 ppm |

📡 Data are transmitted to **ThingSpeak** using simple HTTP `GET` requests—no additional Wi‑Fi libraries required.

---

## 📊 Datasets

- **Source:** MAPCO₂ buoy, NOAA Ship *Ronald H. Brown* (South Georgia Island, 2008 – SO_GasEx project)
- **Selected variables:**
  - `pCO2_5m` → CO₂ concentration (5 m depth)
  - `pH_1m` → pH (1 m depth)
  - `Temp_5m` → Temperature (5 m depth)

These variables were repurposed to simulate soil‑environment behavior for **anomaly detection** experiments.

---

## 🧰 Data Preprocessing (Google Colab)

The MAPCO₂–SAMI dataset was cleaned and structured for ThingSpeak in  
[`Colab/MAPCO2_SAMI_Dataset_To_ThingSpeak.ipynb`](Colab/MAPCO2_SAMI_Dataset_To_ThingSpeak.ipynb).

This notebook:
- Loads the NOAA `MAPCO2_SAMI.csv` dataset  
- Creates ISO timestamps (`created_at`)  
- Removes missing values (`nd` → NaN)  
- Calculates rolling averages and differences  
- Renames columns to match **ThingSpeak fields** (`field1`, `field2`, `field3`)  
- Outputs a ready‑to‑upload CSV for your ThingSpeak channels

---

## 📈 Anomaly Detection Results

### CO₂ Analysis
- Notable deviations: **−20.1 ppm** and **+6.6 ppm**
- Suggest intermittent environmental or operational fluctuations.

### pH Analysis
- Deviations: **−0.0061** and **+0.0318**
- Indicates a largely stable environment with rare anomalies.

**Interpretation:**  
CO₂ variability is higher than pH stability, highlighting possible ventilation or respiration effects in the greenhouse model.

---

## ⚠️ Alerts & Automation

- Anomalous readings trigger **real‑time email notifications**
- Alerts categorize causes:
  - Potential root‑respiration issues  
  - Excessive photosynthetic CO₂ uptake  
- Early warnings allow farmers to apply corrective actions before yield is affected.

---

## ☁️ ThingSpeak Channels

| Channel | Purpose | Channel ID | Read API Key |
|----------|----------|-------------|--------------|
| Sensor Data | Raw Readings | `2555520` | `55MK168WA4TMXD59` |
| Processed Data | Normalized data | `2555429` | `2JJDM9JESCFMGUQU` |
| Anomaly Detection | Alerts & events | `2554118` | `2X8VHUJXRZ4EJ2AU` |

---

## 🧩 Simulation

- [Tinkercad Simulation Link](https://www.tinkercad.com/things/fFUJdAnFs2U-iot-project-iot-soil-sensor-network/editel?sharecode=STVfS4FUMvoL1q-AoY18LC7NOSmIcEi4lP1AU4sPcyY)  
  *(Log in required to view and simulate.)*  
- Arduino Uno prototype with CO₂ and pH monitoring.

---

## 🧠 Conclusion

The project demonstrates a complete IoT pipeline:
- Real‑time soil sensor acquisition  
- Cloud‑based anomaly detection and analytics  
- Automated alerts and decision support  

Together, these tools enable **precision agriculture** and sustainable greenhouse management.

---

## 📜 License

Released under the **MIT License**.  
 Feel free to use or adapt for educational and research purposes.
