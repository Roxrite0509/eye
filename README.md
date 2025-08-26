# eye_PranavPandey
This project is a wearable guidance system for blind and visually impaired users. It combines the Intel RealSense D435i depth camera with AI/LLM-based scene understanding to provide real-time spoken navigation assistance through a bone-conduction earpiece.


#AI-Powered Earpiece for Blind Navigation


#Capture

   The Intel RealSense D435i streams RGB, depth, and IMU data.
   The camera is mounted at eye level (on glasses or a headband).

#Perception (Fast Safety Loop)

    Depth frames are analyzed in real-time (<200 ms).
   If an obstacle is detected within a critical distance (e.g., <0.8m), the system immediately warns the user:
     Warning: obstacle ahead, 0.6 meters.

#Scene Understanding

   Every few seconds, lightweight object detection (YOLO/MobileNet) identifies common objects: stairs, doors, vehicles, people.
   The results are converted into structured descriptions (object + distance + direction).

#Reasoning (LLM Layer)

    An LLM (local quantized model or GPT-4o API) turns perception data into human-friendly guidance.
    Example:

     Input: `{ "left": "chair 1.2m", "center": "stairs 2.5m" }`
     Output: Chair on your left. Move slightly right; stairs 2.5m ahead.

#Output

    Guidance is spoken through text-to-speech** into a bone-conduction earpiece**.
    Urgent alerts can also trigger haptic feedback (vibration).



##Hardware Requirements

 Intel RealSense D435i (Depth + RGB + IMU).
 Compute unit (any of):

 NVIDIA Jetson Orin Nano / Xavier NX (recommended).
 Raspberry Pi 5 (8GB).
 Laptop (for early testing).
 Bluetooth bone-conduction earpiece (e.g., Shokz).
 Portable power bank (10,000mAh+).

##Software Stack

Camera & Depth** [Intel RealSense SDK (librealsense)](https://github.com/IntelRealSense/librealsense), `pyrealsense2`.
Processing**: OpenCV, NumPy, PyTorch.
Object Detection: YOLOv8-nano or MobileNet SSD (optional).
LLM:

   Cloud → OpenAI GPT-4o.
   Local → LLaMA / Mistral (quantized via `llama.cpp`).
   Speech**: Coqui TTS, `pyttsx3`, or system TTS.

This will:

* Continuously stream depth frames.
* Warn if an obstacle is too close.
* Periodically call an LLM for scene description.
* Speak instructions through TTS.

##Roadmap

[x] Depth-based obstacle detection + spoken warnings.
[ ] Object detection (stairs, doors, people).
[ ] LLM integration for natural scene guidance.
[ ] On-device model optimization (Jetson).
[ ] User testing with visually impaired volunteers

Disclaimer

This project is **experimental** and not a certified medical/assistive device.
Use only in controlled environments and with safety supervision.
