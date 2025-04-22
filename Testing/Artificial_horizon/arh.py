import pygame
import time
import os

#os.environ['SDL_VIDEO_WINDOW_POS'] = "-1060,-200"  # Example: Open on the second screen at (1920, 100)


# Initialize Pygame
pygame.init()
screen = pygame.display.set_mode((400, 400))
pygame.display.set_caption("Artificial Horizon")

pitch = 0
up = True
roll = 0  
rolling_right = True

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
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
    pygame.draw.rect(horizon_surface, (160, 230, 255), (100, 0, 200, 200-pitch))

    # Draw black ground
    pygame.draw.rect(horizon_surface, (0, 0, 0), (100, 200-pitch, 200, 400))

    #draw vertical line
    pygame.draw.line(horizon_surface, (0, 0, 0), (200, 0), (200, 200-pitch), 5)  # Vertical line
    pygame.draw.line(horizon_surface, (255, 255, 255), (200, 400), (200, 200-pitch), 5)  # Vertical line

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
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-50), (290, 200-pitch-50), 4)
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+100), (290, 200-pitch+100), 3)  
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-100), (290, 200-pitch-100), 4)
    pygame.draw.line(horizon_surface, (255, 255, 255), (110, 200-pitch+150), (290, 200-pitch+150), 3)  
    pygame.draw.line(horizon_surface, (0, 0, 0), (110, 200-pitch-150), (290, 200-pitch-150), 4)   

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


    print(f'Pitch: {pitch} Roll: {roll}')

    if up:
        pitch += 1
        if pitch >= 100:
            up = False
    else:
        pitch -= 1
        if pitch <= -100:
            up = True

    if rolling_right:
        roll += 0.1
        if roll >= 90:
            rolling_right = False
    else:
        roll -= 0.1
        if roll <= -90:
            rolling_right = True



pygame.quit()