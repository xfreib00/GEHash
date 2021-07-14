#!/usr/bin/env python3

import json
import os
import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
import argparse


def load_data(folder: str = None) -> pd.DataFrame:
    """Load data from folder to Pandas.DataFrame.
       Read all JSON files in given folder and create DataFrame from them.

    Args:
        dir (str, optional): Folder to read data from. Defaults to None.

    Returns:
        pd.DataFrame: DataFrame containing data read from JSON files.
    """
    if not folder:
        raise IOError("Folder not specified")
    dfs = []
    try:
        for f in os.listdir(folder):
            if f.endswith(".json"):
                path = os.path.join(folder, f)
                df = pd.read_json(path)
                dfs.append(df)
    except:
        print("error occured while loading data.")
    temp = pd.concat(dfs, ignore_index=True)
    return temp


def plot_gen_fitness(df: pd.DataFrame, fig_location: str = None,
                     show_plot: bool = False, show_swarm: bool = False):
    """Generate boxplot from provided DataFrame displaying distribution of fitness value
       for each generation.

    Args:
        df (pd.DataFrame): DataFrame containing data to be ploted.
        fig_location (str, optional): Path where to store generated plot. Defaults to None.
        show_plot (bool, optional): Show plot on display. Defaults to False.
        show_swarm (bool, optional): Plot swarmplot over boxplot data. Defaults to False.
    """
    # Create plot object and set data to plot
    sns.set_theme(style="white", context="paper")
    _, ax = plt.subplots(1, 1, figsize=(7, 5))
    data = df
    if data["gen"].max() > 50:
        df1 = df[df["gen"] % 5 == 0]
        data = df1

    sns.boxplot(data=data, x="gen", y="fitness", ax=ax, color="white")
    if show_swarm:
        sns.swarmplot(data=df, x="gen", y="fitness", color=".25")
    ax.set_xlabel("Generation")
    ax.set_ylabel("Fitness")

    if data["gen"].max() > 50:
        for ind, label in enumerate(ax.get_xticklabels()):
            if ind % 5 == 0:  # every 10th label is kept
                label.set_visible(True)
            else:
                label.set_visible(False)

    # If figure location is specified, try to save plot
    if fig_location is not None:
        try:
            plt.savefig(fig_location)
        except FileNotFoundError:
            print("Could not save figure to {}".format(fig_location))

    if show_plot:
        plt.show()


def get_best_code(df: pd.DataFrame) -> str:
    """Return string containing code of best individual.

    Args:
        df (pd.DataFrame): Dataframe of evolution run

    Returns:
        str: Return code of best individual.
    """
    indi = df[(df["fitness"] == df["fitness"].min())
              & (df["status"] == "result")]
    indi = indi.phenotype.apply(pd.Series)
    return indi["code"]


def store_data(df: pd.DataFrame, path: str):
    """Store DataFrame to pickle compressed with gzip.

    Args:
        df (pd.DataFrame): DataFrame to be stored.
        path (str): Path where to store created file.
    """
    df.to_pickle(path="{}.pkl.gz".format(path), compression="gzip")


def load_pkl_data(path: str = None) -> pd.DataFrame:
    """Load DataFrame from pickle file compressed with gzip.

    Args:
        path (str, optional): Path to file. Defaults to None.

    Raises:
        IOError: If path is None, raise.

    Returns:
        pd.DataFrame: Return loaded DataFrame
    """
    if not path:
        raise IOError("No file given")

    df = pd.read_pickle(filepath_or_buffer=path, compression="gzip")

    return df


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--fig_location", "-f", type=str,
                        help="Path to filename")
    parser.add_argument("--show_plot", "-d",
                        action="store_true", help="Display plot on screen")
    parser.add_argument("--show_swarm", "-s", action="store_true",
                        help="Display swarmplot over boxplot")
    parser.add_argument("--input", "-i", type=str,
                        help="Data input. Can be folder or "
                        "pickle file compressed with gzip")
    parser.add_argument("--output_file", "-o", type=str,
                        help="Output file path and name")
    parser.add_argument("--code", "-c", action='store_true',
                        help="Display code of best individual")
    args = parser.parse_args()
    if not args.input.endswith(".pkl.gz"):
        data = load_data(args.input)
    else:
        data = load_pkl_data(args.input)
    plot_gen_fitness(data, args.fig_location, args.show_plot, args.show_swarm)
    if (args.output_file):
        store_data(data, args.output_file)
