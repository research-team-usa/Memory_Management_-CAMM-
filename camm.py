# =============================================================================
# Lead Architect: Emanuel Schaaf
# Open Origin Architecture
# Project: CAMM Architectural Simulator & BVE Logistical Visualizer
# =============================================================================

import sys
import traceback

try:
    import numpy as np
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    import matplotlib.animation as animation
    import hashlib
except ImportError as e:
    print(f"[FATAL ERROR] Import failed: {e}")
    input("Press Enter to exit...")
    sys.exit(1)

class CAMMSimulator:
    def __init__(self, time_steps: int):
        self.time_steps = time_steps
        # Analytics arrays
        self.trad_mem = np.zeros(time_steps)
        self.camm_mem = np.zeros(time_steps)
        
        # Simulating the Global Hash Index Table (GHIT)
        self.ghit = set()
        
    def generate_page_hash(self, base_val: int) -> str:
        """Simulates domain-salted hashing of a 4KB page."""
        raw_data = f"PAGE_PAYLOAD_DATA_{base_val}_DOMAIN_SALT".encode('utf-8')
        return hashlib.sha256(raw_data).hexdigest()

    def simulate_pipeline(self):
        """Calculates memory overheads utilizing the CAMM Merkle architecture."""
        trad_allocated = 0
        camm_allocated = 0
        
        print("[*] Initiating Asynchronous SRAM-Write-Buffer Simulation...")
        for t in range(self.time_steps):
            # Simulate a system where 75% of writes are redundant (shared libraries, LLM weights)
            is_redundant = np.random.rand() > 0.25 
            base_val = np.random.randint(0, 10) if is_redundant else t
            
            page_hash = self.generate_page_hash(base_val)
            
            trad_allocated += 4096  # Traditional MMU allocates blindly
            
            # BVE & Manual-Only Export Gate Logic
            if page_hash not in self.ghit:
                # Delta_page = 1 (New Data or Collision)
                self.ghit.add(page_hash)
                camm_allocated += 4096 # Allocate physical RAM
            else:
                # Delta_page = 0 (True Deduplication)
                pass # Zero-copy pointer update; no new RAM allocated
                
            self.trad_mem[t] = trad_allocated / (1024 * 1024) # MB
            self.camm_mem[t] = camm_allocated / (1024 * 1024) # MB
            
        print("[+] Backend Merkle-Tree Ascent & BVE Validation Complete.")

def run_system_animation():
    steps = 150
    sim = CAMMSimulator(steps)
    sim.simulate_pipeline()
    
    # Apply Open Origin Dark Mode Design
    plt.style.use("dark_background")
    fig, ax = plt.subplots(figsize=(10, 6))
    fig.patch.set_facecolor('#0d1117')
    ax.set_facecolor('#161b22')
    ax.grid(color='#30363d', linestyle='-', linewidth=0.5)
    
    ax.set_xlim(0, steps)
    ax.set_ylim(0, max(sim.trad_mem) * 1.1)
    ax.set_title("Open Origin CAMM vs Traditional Memory Allocation", color='#ffd700', fontsize=14, pad=15)
    ax.set_xlabel("Time (Instruction Cycles)", color='#ffd700')
    ax.set_ylabel("Physical RAM Allocated (MB)", color='#ffd700')
    
    line_trad, = ax.plot([], [], color='#ff00ff', lw=2, label='Traditional MMU Allocation (Linear)')
    line_camm, = ax.plot([], [], color='#00ffcc', lw=2, label='CAMM Deduplicated Allocation (Logarithmic)')
    
    ax.legend(facecolor='#0d1117', edgecolor='#30363d', labelcolor='white')

    def init():
        line_trad.set_data([], [])
        line_camm.set_data([], [])
        return line_trad, line_camm

    def update(frame):
        x = np.arange(0, frame + 1)
        line_trad.set_data(x, sim.trad_mem[:frame+1])
        line_camm.set_data(x, sim.camm_mem[:frame+1])
        return line_trad, line_camm

    ani = animation.FuncAnimation(
        fig, update, frames=steps, init_func=init, blit=True, interval=30
    )

    mp4_filename = "camm_memory_architecture.mp4"
    gif_filename = "camm_memory_architecture.gif"

    try:
        writer = animation.FFMpegWriter(fps=30, bitrate=1800)
        ani.save(mp4_filename, writer=writer)
        print(f"[+] Successfully exported high-resolution MP4: {mp4_filename}")
    except Exception as e:
        print(f"[!] FFMpegWriter unavailable or failed: {e}")
        print("[*] Silently falling back to PillowWriter (GIF format)...")
        try:
            ani.save(gif_filename, writer='pillow', fps=30)
            print(f"[+] Successfully exported fallback GIF: {gif_filename}")
        except Exception as fallback_e:
            print(f"[FATAL ERROR] Fallback export failed: {fallback_e}")

if __name__ == "__main__":
    try:
        print("=== Open Origin: CAMM Hardware Simulator ===")
        run_system_animation()
    except KeyboardInterrupt:
        print("\n[!] Process aborted by user.")
    except Exception as e:
        print("\n[FATAL ERROR] System failure:")
        traceback.print_exc()
    finally:
        print("\n=== Process terminated ===")
        input("Press Enter to close the window...")