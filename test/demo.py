#!/usr/bin/env python3
"""
Python Demo - Gruvbox Crisp Theme
Shows various syntax highlighting features
"""

import sys
import asyncio
from typing import List, Dict, Optional, Union
from dataclasses import dataclass, field
from enum import Enum, auto

# Constants and global variables
API_VERSION = "2.0.1"
MAX_RETRIES = 3
DEBUG_MODE = True

class Status(Enum):
    """Enumeration for status types"""
    PENDING = auto()
    PROCESSING = auto()
    COMPLETED = auto()
    FAILED = auto()

@dataclass
class Configuration:
    """Configuration data class"""
    host: str = "localhost"
    port: int = 8080
    timeout: float = 30.0
    retries: int = MAX_RETRIES
    features: List[str] = field(default_factory=lambda: ["auth", "cache"])

class DataProcessor:
    """Main data processing class"""
    
    def __init__(self, config: Configuration):
        self.config = config
        self._cache: Dict[str, any] = {}
        self._status = Status.PENDING
    
    @property
    def status(self) -> Status:
        """Get current processing status"""
        return self._status
    
    async def process_data(self, data: List[Dict[str, Union[str, int, float]]]) -> Optional[Dict]:
        """
        Process incoming data asynchronously
        
        Args:
            data: List of dictionaries containing mixed types
            
        Returns:
            Processed result or None if failed
        """
        try:
            self._status = Status.PROCESSING
            
            # List comprehension example
            filtered_data = [
                item for item in data 
                if item.get("active", False) and item.get("score", 0) > 0.5
            ]
            
            # Dictionary comprehension
            result = {
                f"item_{idx}": self._transform_item(item)
                for idx, item in enumerate(filtered_data)
            }
            
            # Async operation
            await asyncio.sleep(0.1)
            
            self._status = Status.COMPLETED
            return result
            
        except Exception as e:
            self._status = Status.FAILED
            print(f"Error processing data: {e}", file=sys.stderr)
            return None
    
    def _transform_item(self, item: dict) -> dict:
        """Transform a single item"""
        # Multi-line string
        template = """
        Item: {name}
        Score: {score:.2f}
        Tags: {tags}
        """
        
        # f-string formatting
        description = f"Processed {item.get('name', 'Unknown')} with score {item.get('score', 0):.2%}"
        
        # Regular expression
        import re
        pattern = r'(\w+)@(\w+\.\w+)'
        
        return {
            "original": item,
            "description": description,
            "transformed": True,
            "pattern_match": bool(re.match(pattern, item.get("email", "")))
        }

# Decorator example
def retry(max_attempts: int = 3):
    """Retry decorator for functions"""
    def decorator(func):
        async def wrapper(*args, **kwargs):
            for attempt in range(max_attempts):
                try:
                    return await func(*args, **kwargs)
                except Exception as e:
                    if attempt == max_attempts - 1:
                        raise
                    await asyncio.sleep(2 ** attempt)
            return None
        return wrapper
    return decorator

# Lambda and functional programming
calculate = lambda x, y: x ** 2 + y ** 2
numbers = [1, 2, 3, 4, 5]
squared = list(map(lambda x: x ** 2, numbers))
evens = list(filter(lambda x: x % 2 == 0, numbers))

# Generator example
def fibonacci_generator(n: int):
    """Generate Fibonacci sequence"""
    a, b = 0, 1
    for _ in range(n):
        yield a
        a, b = b, a + b

# Context manager
class ResourceManager:
    def __enter__(self):
        print("Acquiring resource")
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        print("Releasing resource")
        return False

# Main execution
async def main():
    """Main entry point"""
    config = Configuration(
        host="api.example.com",
        port=443,
        timeout=60.0
    )
    
    processor = DataProcessor(config)
    
    # Sample data
    test_data = [
        {"name": "Alpha", "score": 0.95, "active": True, "email": "alpha@test.com"},
        {"name": "Beta", "score": 0.3, "active": True, "email": "beta@test"},
        {"name": "Gamma", "score": 0.85, "active": False, "email": "gamma@test.org"},
    ]
    
    # Process with retry
    @retry(max_attempts=MAX_RETRIES)
    async def process_with_retry():
        return await processor.process_data(test_data)
    
    result = await process_with_retry()
    
    if result:
        print(f"Processing completed: {len(result)} items")
        for key, value in result.items():
            print(f"  {key}: {value.get('description', 'N/A')}")
    else:
        print("Processing failed!")
    
    # Using generator
    print("\nFibonacci sequence:")
    for num in fibonacci_generator(10):
        print(num, end=" ")
    print()
    
    # Using context manager
    with ResourceManager() as rm:
        print("Using resource")

if __name__ == "__main__":
    # Run async main
    asyncio.run(main())