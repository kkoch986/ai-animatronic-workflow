"""
Cactus Whistle Plugin for OpenWebUI
"""

from .main import CactusWhistlePlugin

# Plugin metadata
NAME = "Cactus Whistle"
VERSION = "1.0.0"
DESCRIPTION = "Cactus Whistle speech recognition plugin"

def create_plugin(config=None):
    """
    Create and return a new instance of the Cactus Whistle plugin.
    """
    return CactusWhistlePlugin(config)