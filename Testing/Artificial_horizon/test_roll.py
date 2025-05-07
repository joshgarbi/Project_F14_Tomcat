import pygame
import time
import os

#os.environ['SDL_VIDEO_WINDOW_POS'] = "-1060,-200"  # Example: Open on the second screen at (1920, 100)


# Initialize Pygame
pygame.init()
pygame.joystick.init()
if pygame.joystick.get_count() == 0:
    print("No joystick detected!")
    exit()

joystick = pygame.joystick.Joystick(0)
joystick.init()
print(f"Using joystick: {joystick.get_name()}")

screen = pygame.display.set_mode((400, 400))
pygame.display.set_caption("Artificial Horizon")

def map_value(value, in_min, in_max, out_min, out_max):
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def is_upside_down(roll):
    # Normalize roll to [0, 360)
    normalized_roll = roll % 360

    # Check if roll is between 90° and 270° (upside down)
    if 90 <= normalized_roll <= 270:
        return True
    return False

pitch = 0
pitch_input = 0
up = True
roll = 0  
rolling_right = True
correct_roll = 0
rolled_end = False

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    pitch_input = joystick.get_axis(1)  # Left stick vertical axis (Y-axis)
    roll_input = joystick.get_axis(0)   # Left stick horizontal axis (X-axis)

    #add deadzone
    if abs(pitch_input) < 0.1:
        pitch_input = 0
    if abs(roll_input) < 0.1:
        roll_input = 0

    # print(f"Pitch Input: {pitch_input}, Roll Input: {roll_input}")

    # Map controller input to pitch and roll

    # detect if plane is upside down

    roll += map_value(roll_input, -1, 1, -2, 2)
    
    if is_upside_down(roll) and pitch < 400:
        pitch += map_value(pitch_input, -1, 1, -5, 5)
    if not is_upside_down(roll) and pitch > -400:
        pitch += map_value(pitch_input, -1, 1, 5, -5)
    if is_upside_down(roll) and pitch > 400 and rolled_end == False:
        roll += 180
        rolled_end = True
    if not is_upside_down(roll) and pitch < -400 and rolled_end == False:
        roll += 180
        rolled_end = True
    if is_upside_down(roll) and pitch < -400 and rolled_end == False:
        roll += 180
        rolled_end = True
    if not is_upside_down(roll) and pitch > 400 and rolled_end == False:
        roll += 180
        rolled_end = True

    if -400 < pitch < 400 and rolled_end == True:
        rolled_end = False

    
    

    print(f"Pitch: {pitch}, Roll: {roll}")
    #mask outside of the circle
    mask = pygame.Surface((400, 400), pygame.SRCALPHA)
    mask.fill((0, 0, 0, 0))  # Transparent background
    pygame.draw.circle(mask, (0, 0, 0, 255), (200, 200), 300, 155)  # Black circle

    # Clear screen
    screen.fill((25, 25, 25))

    # Create a separate surface for the horizon
    horizon_surface = pygame.Surface((400, 400), pygame.SRCALPHA)
    horizon_surface.fill((0, 0, 0, 0))  # Transparent background


    # Draw blue sky
    pygame.draw.rect(horizon_surface, (160, 230, 255), (100, -250-pitch, 200, 450))

    # Draw black ground
    pygame.draw.rect(horizon_surface, (0, 0, 0), (100, 200-pitch, 200, 450))

    #draw vertical line
    pygame.draw.line(horizon_surface, (0, 0, 0), (200, -250-pitch), (200, 200-pitch), 5)  # Vertical line
    pygame.draw.line(horizon_surface, (255, 255, 255), (200, 650-pitch), (200, 200-pitch), 5)  # Vertical line

    # Draw 5 Degree attitude lines
    pygame.draw.line(horizon_surface, (255, 255, 255), (185, 200-pitch+25), (215, 200-pitch+25), 3)  
    pygame.draw.line(horizon_surface, (0, 0, 0), (185, 200-pitch-25), (215, 200-pitch-25), 4)     
    pygame.draw.line(horizon_surface, (255, 255, 255), (185, 200-pitch+75), (215, 200-pitch+75), 3)  
    pygame.draw.line(horizon_surface, (0, 0, 0), (185, 200-pitch-75), (215, 200-pitch-75), 4)
    pygame.draw.line(horizon_surface, (255, 255, 255), (185, 200-pitch+125), (215, 200-pitch+125), 3)  
    pygame.draw.line(horizon_surface, (0, 0, 0), (185, 200-pitch-125), (215, 200-pitch-125), 4)  

    # Draw 10 Degree atitude lines
    pygame.draw.line(horizon_surface, (205, 205, 205), (100, 200-pitch), (300, 200-pitch), 5)  # BASE
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+50), (290, 200-pitch+50), 3)  
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-50), (290, 200-pitch-50), 4) # 10
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+100), (290, 200-pitch+100), 3)  
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-100), (290, 200-pitch-100), 4) # 20
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+150), (290, 200-pitch+150), 3)  
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-150), (290, 200-pitch-150), 4) # 30
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+200), (290, 200-pitch+200), 3)
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-200), (290, 200-pitch-200), 4) # 40
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+250), (290, 200-pitch+250), 3)
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-250), (290, 200-pitch-250), 4) # 50
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+300), (290, 200-pitch+300), 3)
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-300), (290, 200-pitch-300), 4) # 60
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+350), (290, 200-pitch+350), 3)
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-350), (290, 200-pitch-350), 4) # 70
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+400), (290, 200-pitch+400), 3)
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-400), (290, 200-pitch-400), 4) # 80
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+450), (290, 200-pitch+450), 3)
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-450), (290, 200-pitch-450), 4) # 90
  

    # Rotate the horizon surface based on the roll angle
    rotated_horizon = pygame.transform.rotate(horizon_surface, roll)

    # Get the new rect of the rotated surface and center it on the screen
    rotated_rect = rotated_horizon.get_rect(center=(200, 200))

    # Blit the rotated horizon onto the main screen
    screen.blit(rotated_horizon, rotated_rect.topleft)


    # Draw plane reticle
    pygame.draw.circle(screen, (255, 255, 255), (200, 200), 7)
    pygame.draw.line(screen, (255, 255, 255), (275, 200), (240, 200), 5) 
    pygame.draw.line(screen, (255, 255, 255), (125, 200), (160, 200), 5) 
    
    screen.blit(mask, (0, 0))

    #draw tilt markers
    triangle_vertices = [(200, 50), (190, 30), (210, 30)]
    pygame.draw.polygon(screen, (255, 255, 255), triangle_vertices)
    pygame.draw.line(screen, (255, 255, 255), (220, 50), (230, 35), 5) # roll right 1
    pygame.draw.line(screen, (255, 255, 255), (180, 50), (170, 35), 5) # roll left 1
    pygame.draw.line(screen, (255, 255, 255), (240, 55), (250, 40), 5) # roll right 2
    pygame.draw.line(screen, (255, 255, 255), (160, 55), (150, 40), 5) # roll left 2
    pygame.draw.line(screen, (255, 255, 255), (350, 200), (375, 200), 5) # roll right 90
    pygame.draw.line(screen, (255, 255, 255), (25, 200), (50, 200), 5) # roll left 90
    # draw roll 45 degrees
    pygame.draw.line(screen, (255, 255, 255), (330, 115), (345, 102), 5) # roll right 45
    pygame.draw.line(screen, (255, 255, 255), (70, 115), (55, 102), 5) # roll left 45



    # Draw white outer circle
    pygame.draw.circle(screen, (0, 0, 0), (200, 200), 150, 5)

    pygame.display.flip()
    time.sleep(0.016)  # 60 FPS
        
pygame.quit()


