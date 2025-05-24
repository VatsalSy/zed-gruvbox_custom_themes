/**
 * JavaScript Demo - Gruvbox Crisp Theme
 * Demonstrates various JS syntax highlighting features
 */

// Import statements
import { createServer } from 'http';
import * as path from 'path';
import EventEmitter from 'events';

// Constants and variables
const API_KEY = 'your-api-key-here';
const MAX_CONNECTIONS = 100;
let connectionCount = 0;
var legacyVar = 'still supported';

// Class definition with inheritance
class DataService extends EventEmitter {
    #privateField = 'hidden';
    static instances = 0;
    
    constructor(config = {}) {
        super();
        this.config = {
            host: 'localhost',
            port: 3000,
            timeout: 5000,
            ...config
        };
        DataService.instances++;
    }
    
    // Async method with error handling
    async fetchData(endpoint, options = {}) {
        try {
            const url = new URL(endpoint, `https://${this.config.host}`);
            const response = await fetch(url, {
                method: options.method || 'GET',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${API_KEY}`,
                    ...options.headers
                },
                body: options.body ? JSON.stringify(options.body) : undefined
            });
            
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            
            return await response.json();
        } catch (error) {
            this.emit('error', error);
            throw error;
        }
    }
    
    // Generator function
    *generateIds(count = 10) {
        let id = 0;
        while (id < count) {
            yield `ID_${Date.now()}_${id++}`;
        }
    }
    
    // Private method
    #validateConfig() {
        const required = ['host', 'port'];
        return required.every(key => this.config[key] !== undefined);
    }
}

// Arrow functions and functional programming
const processArray = (arr) => arr
    .filter(item => item.active)
    .map(item => ({
        ...item,
        processed: true,
        timestamp: Date.now()
    }))
    .reduce((acc, item) => {
        acc[item.id] = item;
        return acc;
    }, {});

// Template literals and string manipulation
const createMessage = (user, action) => {
    const timestamp = new Date().toISOString();
    return `[${timestamp}] User "${user}" performed action: ${action}`;
};

// Regular expressions
const emailRegex = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
const phoneRegex = /^\+?[\d\s()-]+$/;

// Object destructuring and spread
const userDefaults = {
    role: 'user',
    active: true,
    permissions: ['read']
};

const createUser = ({ name, email, ...overrides }) => ({
    id: Math.random().toString(36).substr(2, 9),
    name,
    email,
    ...userDefaults,
    ...overrides,
    createdAt: new Date()
});

// Promise handling and async patterns
const delay = (ms) => new Promise(resolve => setTimeout(resolve, ms));

async function processQueue(queue) {
    const results = [];
    
    for await (const item of queue) {
        console.log(`Processing item: ${item.id}`);
        await delay(100);
        
        const result = await Promise.race([
            processItem(item),
            delay(5000).then(() => {
                throw new Error('Processing timeout');
            })
        ]);
        
        results.push(result);
    }
    
    return results;
}

// Closure example
function createCounter(initialValue = 0) {
    let count = initialValue;
    
    return {
        increment() { return ++count; },
        decrement() { return --count; },
        get value() { return count; },
        reset() { count = initialValue; }
    };
}

// Symbol usage
const SECRET_KEY = Symbol('secret');
const metadata = Symbol.for('metadata');

// WeakMap for private data
const privateData = new WeakMap();

class SecureStore {
    constructor() {
        privateData.set(this, {
            [SECRET_KEY]: crypto.randomUUID()
        });
    }
    
    getSecret() {
        return privateData.get(this)[SECRET_KEY];
    }
}

// Proxy example
const createObservable = (target) => {
    return new Proxy(target, {
        get(obj, prop) {
            console.log(`Accessing property: ${String(prop)}`);
            return obj[prop];
        },
        set(obj, prop, value) {
            console.log(`Setting ${String(prop)} = ${value}`);
            obj[prop] = value;
            return true;
        }
    });
};

// Modern array methods
const numbers = [1, 2, 3, 4, 5];
const doubled = numbers.map(n => n * 2);
const sum = numbers.reduce((a, b) => a + b, 0);
const hasEven = numbers.some(n => n % 2 === 0);
const allPositive = numbers.every(n => n > 0);
const found = numbers.find(n => n > 3);
const foundIndex = numbers.findIndex(n => n > 3);

// Set and Map usage
const uniqueValues = new Set([1, 2, 2, 3, 3, 4]);
const cache = new Map();
cache.set('key1', { data: 'value1' });
cache.set('key2', { data: 'value2' });

// Optional chaining and nullish coalescing
const config = {
    server: {
        port: 3000
    }
};

const port = config.server?.port ?? 8080;
const host = config.server?.host ?? 'localhost';

// Dynamic imports
const loadModule = async (moduleName) => {
    try {
        const module = await import(`./${moduleName}.js`);
        return module.default;
    } catch (error) {
        console.error(`Failed to load module: ${moduleName}`, error);
        return null;
    }
};

// Error types
class ValidationError extends Error {
    constructor(field, value) {
        super(`Invalid value for field '${field}': ${value}`);
        this.name = 'ValidationError';
        this.field = field;
        this.value = value;
    }
}

// Export examples
export default DataService;
export { createUser, processQueue, ValidationError };
export const VERSION = '1.0.0';