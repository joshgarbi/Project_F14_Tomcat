import pygame
import time
import os

# Initialize Pygame
pygame.init()
pygame.joystick.init()  # Initialize joystick module

# Check for connected joysticks
if pygame.joystick.get_count() == 0:
    print("No joystick detected!")
    exit()

# Initialize the first joystick
joystick = pygame.joystick.Joystick(0)
joystick.init()
print(f"Using joystick: {joystick.get_name()}")

# Screen setup
screen = pygame.display.set_mode((400, 400))
pygame.display.set_caption("Artificial Horizon")

def map_value(value, in_min, in_max, out_min, out_max):
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

pitch = 0
roll = 0
running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Read controller input
    pitch_input = joystick.get_axis(1)  # Left stick vertical axis (Y-axis)
    roll_input = joystick.get_axis(0)   # Left stick horizontal axis (X-axis)

    # Map controller input to pitch and roll
    pitch = map_value(pitch_input, -1, 1, -90, 90)  # Map Y-axis to pitch (-90 to 90 degrees)
    roll = map_value(roll_input, -1, 1, -180, 180)  # Map X-axis to roll (-180 to 180 degrees)

    # Clear screen
    screen.fill((25, 25, 25))

    # Create a separate surface for the horizon
    horizon_surface = pygame.Surface((400, 400), pygame.SRCALPHA)
    horizon_surface.fill((0, 0, 0, 0))  # Transparent background

    # Draw blue sky
    pygame.draw.rect(horizon_surface, (160, 230, 255), (0, 0, 400, 200 - pitch))

    # Draw black ground
    pygame.draw.rect(horizon_surface, (0, 0, 0), (0, 200 - pitch, 400, 400))

    # Rotate the horizon surface based on the roll angle
    rotated_horizon = pygame.transform.rotate(horizon_surface, roll)

    # Get the new rect of the rotated surface and center it on the screen
    rotated_rect = rotated_horizon.get_rect(center=(200, 200))

    # Blit the rotated horizon onto the main screen
    screen.blit(rotated_horizon, rotated_rect.topleft)

    # Draw plane reticle (fixed in the center)
    pygame.draw.circle(screen, (255, 255, 255), (200, 200), 7)
    pygame.draw.line(screen, (255, 255, 255), (275, 200), (240, 200), 5)
    pygame.draw.line(screen, (255, 255, 255), (125, 200), (160, 200), 5)

    # Draw white outer circle
    pygame.draw.circle(screen, (255, 255, 255), (200, 200), 150, 5)

    pygame.display.flip()
    time.sleep(0.016)  # 60 FPS

    print(f"Pitch: {pitch:.2f}, Roll: {roll:.2f}")

pygame.quit()