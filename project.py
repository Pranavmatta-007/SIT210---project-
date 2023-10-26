import tkinter as tk
from tkinter import ttk
import paho.mqtt.client as mqtt

def send_to_arduino():
    chemical_1 = dropdown_1.get()
    concentration_1 = entry_1.get()

    chemical_2 = dropdown_2.get()
    concentration_2 = entry_2.get()

    # Initialize MQTT client
    client = mqtt.Client()
    client.connect(broker_address, 1883)
    
    # Publish data to the Arduino
    #print(topic, f"Chemical 1: {chemical_1}, Concentration 1: {concentration_1}")
    client.publish(topic, f"{concentration_2}")
    client.publish(topic2, f"{concentration_1}")
    client.publish(topic3, f"{chemical_1}")
    client.publish(topic4, f"{chemical_2}")
    # Disconnect MQTT client
    client.disconnect()

    print("Data sent to Arduino.")

# Create GUI
root = tk.Tk()
root.title("Chemical Selection GUI")

# Select Chemical 1 (Top Left)
frame_1 = ttk.Frame(root, padding=10)
frame_1.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

# ... (Your existing GUI code)
label_1 = tk.Label(frame_1, text="Select Chemical 1:", font=("Arial", 12))
label_1.grid(row=0, column=0, pady=5)

chemicals = ['ACETIC ACID ', 'SODIUM ACETATE', 'HCL']
dropdown_1 = ttk.Combobox(frame_1, values=chemicals, font=("Arial", 10))
dropdown_1.set(chemicals[0])
dropdown_1.grid(row=1, column=0, pady=5)

label_concentration_1 = tk.Label(frame_1, text="Enter Volume 1:", font=("Arial", 12))
label_concentration_1.grid(row=2, column=0, pady=5)

entry_1 = tk.Entry(frame_1, font=("Arial", 10))
entry_1.grid(row=3, column=0, pady=5)


# Select Chemical 2 (Top Right)
frame_2 = ttk.Frame(root, padding=10)
frame_2.grid(row=0, column=1, padx=10, pady=10, sticky="nsew")

label_2 = tk.Label(frame_2, text="Select Chemical 2:", font=("Arial", 12))
label_2.grid(row=0, column=0, pady=5)

dropdown_2 = ttk.Combobox(frame_2, values=chemicals, font=("Arial", 10))
dropdown_2.set(chemicals[0])
dropdown_2.grid(row=1, column=0, pady=5)

label_concentration_2 = tk.Label(frame_2, text="Enter Volume 2:", font=("Arial", 12))
label_concentration_2.grid(row=2, column=0, pady=5)

entry_2 = tk.Entry(frame_2, font=("Arial", 10))
entry_2.grid(row=3, column=0, pady=5)

# Define MQTT parameters
broker_address = "broker.hivemq.com"
topic = "pranav"
topic2 = "pranav1"
topic3 = "pranav2"
topic4 = "pranav3"

# Submit button with styling
submit_button = tk.Button(root, text="Submit", command=send_to_arduino, font=("Arial", 12), bg="green", fg="white")
submit_button.grid(row=1, column=0, columnspan=2, pady=10)

# Configure root window background color
root.configure(bg="#f0f0f0")

# Set row and column weights to make the columns expandable
root.grid_rowconfigure(0, weight=1)
root.grid_columnconfigure(0, weight=1)
root.grid_columnconfigure(1, weight=1)

root.mainloop()
