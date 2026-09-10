import process from 'process';
import { Compile } from './abytec.js';

async function main() {
	const args = process.argv.slice(2);
	if (args.length < 1) {
		console.error("Uso: node main.js <archivo.paxo> [output.pbc] [-d]");
		process.exit(1);
	}

	const inputFile = args[0];
	let outputFile = inputFile.replace(/\.paxo$/, "") + ".pbc";
	let dump = false;

	for (let i = 1; i < args.length; i++) {
		if (args[i] === "-d") {
			dump = true;
		} else {
			outputFile = args[i];
		}
	}

	try {
		await Compile(inputFile, outputFile, dump);
	} catch (err) {
		console.error(err.message);
		process.exit(1);
	}
}

main();
