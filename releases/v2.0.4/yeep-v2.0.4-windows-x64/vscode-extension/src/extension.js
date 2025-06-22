const vscode = require('vscode');
const { exec } = require('child_process');
const path = require('path');

/**
 * @param {vscode.ExtensionContext} context
 */
function activate(context) {
    console.log('Yeep Programming Language extension is now active!');

    // Register command to run Yeep file
    let runFileCommand = vscode.commands.registerCommand('yeep.runFile', function () {
        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            vscode.window.showErrorMessage('No active Yeep file to run');
            return;
        }

        const document = editor.document;
        if (document.languageId !== 'yeep') {
            vscode.window.showErrorMessage('Active file is not a Yeep file');
            return;
        }

        // Save the file first
        document.save().then(() => {
            const filePath = document.fileName;
            const fileName = path.basename(filePath);
            
            // Create or show terminal
            const terminal = vscode.window.createTerminal(`Yeep: ${fileName}`);
            terminal.show();
            
            // Run the Yeep file
            terminal.sendText(`yeep "${filePath}"`);
        });
    });

    // Register command to start Yeep REPL
    let replCommand = vscode.commands.registerCommand('yeep.runInteractive', function () {
        // Create or show terminal for REPL
        const terminal = vscode.window.createTerminal('Yeep REPL');
        terminal.show();
        
        // Start interactive Yeep
        terminal.sendText('yeep');
        
        vscode.window.showInformationMessage('Yeep REPL started! Type "help" for commands, "exit" to quit.');
    });

    // Register hover provider for built-in functions
    let hoverProvider = vscode.languages.registerHoverProvider('yeep', {
        provideHover(document, position, token) {
            const range = document.getWordRangeAtPosition(position);
            const word = document.getText(range);
              const builtinFunctions = {
                'print': {
                    signature: 'print(value)',
                    description: 'Prints a value to the console',
                    example: 'print("Hello, World!");'
                },
                'str': {
                    signature: 'str(value)',
                    description: 'Converts a value to a string',
                    example: 'let text = str(123); // Returns "123"'
                },
                'sqrt': {
                    signature: 'sqrt(number)',
                    description: 'Returns the square root of a number',
                    example: 'let result = sqrt(16); // Returns 4'
                },
                'max': {
                    signature: 'max(a, b, ...)',
                    description: 'Returns the maximum value from the arguments',
                    example: 'let result = max(1, 8, 3); // Returns 8'
                },
                'length': {
                    signature: 'length(string_or_array)',
                    description: 'Returns the length of a string or array',
                    example: 'let len = length("Hello"); // Returns 5'
                },
                'uppercase': {
                    signature: 'uppercase(string)',
                    description: 'Converts a string to uppercase',
                    example: 'let upper = uppercase("hello"); // Returns "HELLO"'
                },
                'size': {
                    signature: 'size(array)',
                    description: 'Returns the size of an array',
                    example: 'let s = size([1, 2, 3]); // Returns 3'
                },
                'get': {
                    signature: 'get(array, index)',
                    description: 'Gets an element from an array at the specified index',
                    example: 'let element = get(numbers, 0); // Returns first element'
                },
                'push': {
                    signature: 'push(array, value)',
                    description: 'Adds a value to the end of an array and returns the new array',
                    example: 'let newArray = push(numbers, 6);'
                },
                'input': {
                    signature: 'input(prompt)',
                    description: 'Gets user input with an optional prompt',
                    example: 'let name = input("Enter your name: ");'
                },
                'type': {
                    signature: 'type(value)',
                    description: 'Returns the type of a value as a string',
                    example: 'let t = type(42); // Returns "number"'
                },
                'num': {
                    signature: 'num(string)',
                    description: 'Converts a string to a number',
                    example: 'let number = num("42"); // Returns 42'
                },
                'abs': {
                    signature: 'abs(number)',
                    description: 'Returns the absolute value of a number',
                    example: 'let result = abs(-5); // Returns 5'
                },
                'floor': {
                    signature: 'floor(number)',
                    description: 'Returns the largest integer less than or equal to the number',
                    example: 'let result = floor(3.7); // Returns 3'
                },
                'ceil': {
                    signature: 'ceil(number)',
                    description: 'Returns the smallest integer greater than or equal to the number',
                    example: 'let result = ceil(3.2); // Returns 4'
                },
                'round': {
                    signature: 'round(number)',
                    description: 'Returns the number rounded to the nearest integer',
                    example: 'let result = round(3.6); // Returns 4'
                },
                'random': {
                    signature: 'random()',
                    description: 'Returns a random number between 0 and 1',
                    example: 'let rand = random(); // Returns 0.234...'
                }
            };
            
            if (builtinFunctions[word]) {
                const func = builtinFunctions[word];
                const contents = new vscode.MarkdownString();
                contents.appendCodeblock(func.signature, 'yeep');
                contents.appendMarkdown(func.description);
                contents.appendMarkdown('\n\n**Example:**');
                contents.appendCodeblock(func.example, 'yeep');
                
                return new vscode.Hover(contents);
            }
        }
    });

    // Register completion provider
    let completionProvider = vscode.languages.registerCompletionItemProvider('yeep', {
        provideCompletionItems(document, position, token, context) {
            const completions = [];
              // Keywords
            const keywords = ['if', 'else', 'while', 'for', 'fun', 'return', 'let', 'true', 'false', 'and', 'or', 'not'];
            keywords.forEach(keyword => {
                const item = new vscode.CompletionItem(keyword, vscode.CompletionItemKind.Keyword);
                item.detail = 'Yeep keyword';
                completions.push(item);
            });
            
            // Built-in functions
            const builtins = ['print', 'str', 'sqrt', 'max', 'length', 'uppercase', 'size', 'get', 'push', 'input', 'type', 'num', 'abs', 'floor', 'ceil', 'round', 'random'];
            builtins.forEach(builtin => {
                const item = new vscode.CompletionItem(builtin, vscode.CompletionItemKind.Function);
                item.detail = 'Yeep built-in function';
                completions.push(item);
            });
            
            return completions;
        }
    });

    // Add to subscriptions
    context.subscriptions.push(runFileCommand);
    context.subscriptions.push(replCommand);
    context.subscriptions.push(hoverProvider);
    context.subscriptions.push(completionProvider);
}

function deactivate() {}

module.exports = {
    activate,
    deactivate
};
